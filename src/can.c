#include "stm32h7xx.h"
#include "stm32h7xx_hal_dma.h"
#include "stm32h7xx_hal_rcc.h"
#include "stm32h7xx_hal_tim.h"
#include "stm32h7xx_hal_gpio.h"
#include "stm32h7xx_hal_cortex.h"
#include <stdio.h>
#include "can.h"
#include <stdbool.h>
#include "usart.h"

void (*timer4_callback_handler)(void) = NULL;
static void sync_callback(void);

static uint32_t can_baud = 500000;
static uint32_t can_ticks_per_cycle;
static uint32_t can_initial_delay;

static TIM_Base_InitTypeDef TIM_InitStructure; 
static volatile uint16_t bits_read = 0;
static volatile uint8_t last_bit = 0;
static volatile uint8_t same_bits_count = 0;
static volatile uint32_t arbid;
volatile uint32_t attack_arbid = 0;
static volatile uint16_t msg_byte = 0;
static volatile uint8_t message[8];
static volatile uint8_t extended_arbid = 0;
static volatile uint8_t msg_len = 0;
static volatile uint8_t frame_done = 0;
static volatile uint32_t frames_seen = 0;

static volatile uint8_t synchronized = 0;

const uint32_t TIMER_PERIOD_NS = 50;

/* Start initializing the CAN peripheral */
void can_init()
{
    /* Enable TIM4 clock */
    __HAL_RCC_TIM4_CLK_ENABLE();

    /* Set up the TIM4 interrupt */
    HAL_NVIC_SetPriority(TIM4_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(TIM4_IRQn);

    /* Set up the TIM4 peripheral */
    TIM_InitStructure.ClockDivision = TIM_CLOCKDIVISION_DIV4;
    TIM_InitStructure.Prescaler = 9; /* APB1 clock is at 100 MHz, and this timer counts at twice that speed. Count every 500 ns. Note: The prescale value used is the register value + 1 */
    TIM_InitStructure.CounterMode = TIM_COUNTERMODE_UP;
    TIM_InitStructure.Period = 2000 / TIMER_PERIOD_NS; /* Start with 2 microseconds, which equates to 500 KBPS */
    TIM_Base_SetConfig(TIM4, &TIM_InitStructure);
    timer4_callback_handler = NULL;

    /* Set up the EXTI interrupt */
    HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
}

/* Checks to see if we've received a message and prints it out */
void can_poll()
{
    if(frame_done)
    {
        frame_done = 0;
        //printf("Arbid: %lx\r\n", arbid);
        //printf("Msg: %x %x %x %x %x %x %x %x\r\n", message[0], message[1], message[2], message[3], message[4], message[5], message[6], message[7]);
        /* After 128 frames, turn the LED on */
        if ((frames_seen & 0x000000FF) == 128)
        {
            BSP_LED_On(LED2);
        }
        else if((frames_seen & 0xFF) == 0)
        {
            BSP_LED_Off(LED2);
        }
    }
}

/* Synchronize to the CAN bus. Start sampling at 2x baud rate and make sure we see an end of frame */
void can_sync()
{
    TIM4->ARR = can_ticks_per_cycle >> 1;
    TIM4->CNT = 0;
    timer4_callback_handler = sync_callback;
    synchronized = 0;
    same_bits_count = 0;

    // Enable timer and interrupt
    TIM4->DIER |= TIM_IT_UPDATE;
    TIM4->CR1 |= TIM_CR1_CEN;

    write_string("Synchronizing CAN bus...");
    while(!synchronized);
    write_string("Done\r\n");

    // Enable the external interrupt on the RX pin
    while(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_12) > 0)
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_12); // Clear any pending interrupt
    while(NVIC_GetPendingIRQ(EXTI15_10_IRQn) == 1)
        NVIC_ClearPendingIRQ(EXTI15_10_IRQn);
    NVIC_EnableIRQ(EXTI15_10_IRQn);
}

/* Interrupt callback for synchronizing to the CAN bus */
static void sync_callback(void)
{
    /* Check to see if we are getting a 1 */
    if((GPIOB->IDR & GPIO_PIN_12) > 0)
        same_bits_count++;
    else
        same_bits_count = 0;

    if(same_bits_count >= 14)
    {
        synchronized = 1;
        can_timer_stop();
    }
}

/* Interrupt callback for sampling a CAN message. Uses the 
 * following global variables
 *
 * uint16_t bits_read = 0; 
 * uint8_t  last_bit = 0; 
 * uint8_t  same_bits_count = 0; 
 * uint32_t arbid; 
 * uint16_t msg_byte = 0; 
 * uint8_t  message[8]; 
 * uint8_t  extended_arbid = 0;
 * uint8_t  msg_len = 0;
 */
static void sample_callback(void)
{
    uint16_t bit_read = 0;
    if (GPIOB->IDR & GPIO_PIN_12)
        bit_read = 1;


    /* Check to see if this is a stuff bit */
    if (same_bits_count >= 5) /* This is a stuff bit */
        same_bits_count = 0;
    else /* Not a stuff bit */
    {
        bits_read++;

        /* Track consecutive bits */
        if(bit_read == last_bit)
            same_bits_count++;
        else
            same_bits_count = 1;
        last_bit = bit_read;

        /* Populate the correct item based on position */
        // bit 1 is SOF, ignore it
        if(bits_read >= 2 && bits_read <= 12)
        {
            arbid <<= 1;
            arbid |= bit_read;
        }

        // bit 13 remote transmission request
        else if(bits_read == 14)
            extended_arbid = bit_read;

        /* From here, message length is based on whether or not we have an extended identifier. */
        if(extended_arbid == 0 && bits_read > 14)
        {
            // bit 15 is reserved
            if(bits_read >= 16 && bits_read <= 19)
            {
                msg_len <<= 1;
                msg_len |= bit_read;
            }
            else if(bits_read >= 20 && bits_read < (20 + (8 * msg_len)))
            {
                message[msg_byte] <<= 1;
                message[msg_byte] |= bit_read;

                if(bits_read - 20 - (msg_byte * 8) >= 7)
                    msg_byte++;
            }
        }
        else if (bits_read > 14)
        {
            if(bits_read >= 15 && bits_read <= 32)
            {
                arbid <<= 1;
                arbid |= bit_read;
            }
            // bit 33 is remote transmission request
            // bits 34 and 35 are reserved
            else if(bits_read >= 36 && bits_read <= 39)
            {
                msg_len <<= 1;
                msg_len |= bit_read;
            }
            else if(bits_read >= 40 && bits_read < (40 + (8 * msg_len)))
            {
                message[msg_byte] <<= 1;
                message[msg_byte] |= bit_read;

                if(bits_read - 40 - (msg_byte * 8) >= 7)
                    msg_byte++;
            }
         }
    }
    /* Currently skipping the last 18 bits of CRC and ACKS */

    if((extended_arbid == 0 && bits_read > (20 + 18 + (8 * msg_len))) ||
       (extended_arbid == 1 && bits_read > (40 + 18 + (8 * msg_len))))
    {
        can_timer_stop();
        // Enable the external interrupt on the RX pin
        frame_done = 1;
        frames_seen++;

        // Enable the external interrupt on the RX pin
        while(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_12) > 0)
            __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_12); // Clear any pending interrupt
        while(NVIC_GetPendingIRQ(EXTI15_10_IRQn) == 1)
            NVIC_ClearPendingIRQ(EXTI15_10_IRQn);
        HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
    }
}

void can_timer_stop()
{
    /* Disable the overflow interrupt and timer */
    TIM4->DIER &= ~TIM_IT_UPDATE;
    TIM4->CR1 &= ~TIM_CR1_CEN;

    /* Disable the callback */
    timer4_callback_handler = NULL;
}

void TIM4_IRQHandler(void)
{
GPIOA->ODR |= GPIO_PIN_15;
    TIM4->SR = ~TIM_IT_UPDATE;
    TIM4->ARR = can_ticks_per_cycle;
    if(timer4_callback_handler != NULL)
    {
        timer4_callback_handler();
    }
GPIOA->ODR &= ~GPIO_PIN_15;
}

void EXTI15_10_IRQHandler(void)
{
GPIOA->ODR |= GPIO_PIN_4;
    __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_12); // Clear any pending interrupt

    HAL_NVIC_DisableIRQ(EXTI15_10_IRQn);
    /* Start the timer to start sampling the incoming CAN message */
    TIM4->ARR = can_ticks_per_cycle + can_initial_delay;
    TIM4->CNT = 0;

    timer4_callback_handler = sample_callback;
    same_bits_count = 0;
    bits_read = 1;
    last_bit = 0;
    arbid = 0;
    msg_byte = 0;
    extended_arbid = 0;
    msg_len = 0;

    TIM4->DIER |= TIM_IT_UPDATE;
    TIM4->CR1 |= TIM_CR1_CEN;

    /* Set the ARR back to the correct value */
GPIOA->ODR &= ~GPIO_PIN_4;
}

void setCanBaudrate(long int baud)
{
    can_baud = baud;
    can_ticks_per_cycle = ((1000000000 / can_baud) / TIMER_PERIOD_NS) - 1;
    /* Calculate the 1/2 cycle delay so that the sampling interrupt happens in the middle of the bit.
     * It takes appx 500ns to set up the initial interrupt, so we have that delay already */
    can_initial_delay = (can_ticks_per_cycle >> 1) - (500 / TIMER_PERIOD_NS);
}

