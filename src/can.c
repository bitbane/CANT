#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_exti.h"
#include "stm32f4xx_syscfg.h"
#include <stdio.h>
#include "can.h"
#include <stdbool.h>

void (*timer4_callback_handler)(void) = NULL;
static void sync_callback(void);

static uint32_t can_baud = 500000;
static uint32_t can_ticks_per_cycle;

static volatile uint16_t bits_read = 0;
static volatile uint8_t last_bit = 0;
static volatile uint8_t same_bits_count = 0;
static volatile uint32_t arbid;
static volatile uint16_t msg_byte = 0;
static volatile uint8_t message[8];
static volatile uint8_t extended_arbid = 0;
static volatile uint8_t msg_len = 0;
static volatile uint8_t frame_done = 0;

static volatile uint8_t synchronized = 0;

const uint32_t TIMER_PERIOD_NS = 500;

/* Start initializing the CAN peripheral */
void can_init()
{
    NVIC_InitTypeDef NVIC_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_InitStructure; 
    EXTI_InitTypeDef EXTI_InitStructure;

    /* Enable TIM4 clock */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

    /* Set up the TIM4 interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* Set up the TIM4 peripheral */
    TIM_InitStructure.TIM_ClockDivision = TIM_CKD_DIV4;
    TIM_InitStructure.TIM_Prescaler = 41; /* APB1 clock is at 42 MHz, and this timer counts at twice that speed. Count every 250 ns. Note: The prescale value used is the register value + 1 */
    TIM_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_InitStructure.TIM_Period = 4; /* Start with 2 microseconds, which equates to 500 KBPS */
    TIM_TimeBaseInit(TIM4, &TIM_InitStructure);
    timer4_callback_handler = NULL;

    /* Enable the EXTI clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

    /* Set up the EXTI Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* Set up the EXTI0 peripheral */
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource0);
    EXTI_InitStructure.EXTI_Line = EXTI_Line0;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
    EXTI->IMR &= ~EXTI_Line0; // Disable EXTI interrupt
}

/* Checks to see if we've received a message and prints it out */
void can_poll()
{
    if(frame_done)
    {
        frame_done = 0;
        printf("Arbid: %lx\r\n", arbid);
        printf("Msg: %x %x %x %x %x %x %x %x\r\n", message[0], message[1], message[2], message[3], message[4], message[5], message[6], message[7]);
    }
}

/* Synchronize to the CAN bus. Start sampling at 4x baud rate and make sure we see an end of frame */
void can_sync()
{
    TIM_SetAutoreload(TIM4, can_ticks_per_cycle >> 1);
    TIM_SetCounter(TIM4, 0);
    timer4_callback_handler = sync_callback;
    synchronized = 0;
    same_bits_count = 0;

    TIM_Cmd(TIM4, ENABLE);
    TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);

    printf("Synchronizing CAN bus...\r\n");
    while(!synchronized);

    // Enable the external interrupt on the RX pin
    EXTI->PR |= EXTI_Line0; // Clear any pending interrupt
    EXTI->IMR |= EXTI_Line0; // Enable EXTI interrupt

    printf("Done\r\n");
}

/* Interrupt callback for synchronizing to the CAN bus */
static void sync_callback(void)
{
    /* Check to see if we are getting a 1 */
    if((GPIOD->IDR & 0x1) > 0)
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
    volatile uint8_t bit_read = GPIOD->IDR & 0x01;


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

        // Enable the external interrupt on the RX pin
        EXTI->PR |= EXTI_Line0; // Clear any pending interrupt
        EXTI->IMR |= EXTI_Line0; // Enable EXTI interrupt
    }
}

void can_timer_stop()
{
    TIM_Cmd(TIM4, DISABLE);

    /* Disable the overflow interrupt */
    TIM_ITConfig(TIM4, TIM_IT_Update, DISABLE);

    /* Disable the callback */
    timer4_callback_handler = NULL;
}

void TIM4_IRQHandler(void)
{
    GPIOD->ODR |= GPIO_Pin_4;
    TIM4->SR = ~TIM_IT_Update;
    if(timer4_callback_handler != NULL)
    {
        timer4_callback_handler();
    }
    GPIOD->ODR &= ~GPIO_Pin_4;
}

void EXTI0_IRQHandler(void)
{
    GPIOD->ODR |= GPIO_Pin_4;
    EXTI->PR = EXTI_Line0; // Clear pending interrupt
    EXTI->IMR &= ~EXTI_Line0; // Disable EXTI interrupt

    /* Start the timer to start sampling the incoming CAN message */
    TIM_SetAutoreload(TIM4, can_ticks_per_cycle);
    TIM_SetCounter(TIM4, 0);
    
    timer4_callback_handler = sample_callback;
    same_bits_count = 0;
    bits_read = 1;
    last_bit = 0;
    arbid = 0;
    msg_byte = 0;
    extended_arbid = 0;
    msg_len = 0;

    TIM_Cmd(TIM4, ENABLE);
    TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
    GPIOD->ODR &= ~GPIO_Pin_4;
}

void setCanBaudrate(long int baud)
{
    can_baud = baud;
    can_ticks_per_cycle = ((1000000000 / can_baud) / TIMER_PERIOD_NS) - 1;
}

