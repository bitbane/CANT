#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "usb.h"
#include "tusb.h"
#include "fsl_clock.h"

volatile uint8_t rx_buffer[RX_BUFFER_SIZE];
volatile uint8_t rx_counter = 0;

/* Initialize USB */
void USB_Init()
{
    CLOCK_EnableUsbhs0PhyPllClock(kCLOCK_Usbphy480M, 480000000U);
    CLOCK_EnableUsbhs0Clock(kCLOCK_Usb480M, 480000000U);

    USBPHY_Type* usb_phy;

    usb_phy = USBPHY1;

    // Enable PHY support for Low speed device + LS via FS Hub
    usb_phy->CTRL |= USBPHY_CTRL_SET_ENUTMILEVEL2_MASK | USBPHY_CTRL_SET_ENUTMILEVEL3_MASK;

    // Enable all power for normal operation
    usb_phy->PWD = 0;

    // TX Timing
    uint32_t phytx = usb_phy->TX;
    phytx &= ~(USBPHY_TX_D_CAL_MASK | USBPHY_TX_TXCAL45DM_MASK | USBPHY_TX_TXCAL45DP_MASK);
    phytx |= USBPHY_TX_D_CAL(0x0C) | USBPHY_TX_TXCAL45DP(0x06) | USBPHY_TX_TXCAL45DM(0x06);
    usb_phy->TX = phytx;
}

void usb_serial_task()
{
    // connected() check for DTR bit
    // Most but not all terminal client set this when making connection
    // if ( tud_cdc_connected() )
    {
        // connected and there are data available
        if ( tud_cdc_available() )
        {
            // read datas
            char buf[64];
            uint32_t count = tud_cdc_read(buf, sizeof(buf));
            uint32_t buf_idx = 0;

            // Add to RX Buffer
            while((rx_counter < RX_BUFFER_SIZE) && (buf_idx < count))
            {
                /* Handle backspace/delete character */
                if(((buf[buf_idx] == '\b') || (buf[buf_idx] == 0x7f)) && rx_counter > 0)
                {
                    rx_counter--;
                    buf_idx++;
                    continue;
                }
                rx_buffer[rx_counter++] = buf[buf_idx++];
            }

            // Echo back
            // Note: Skip echo by commenting out write() and write_flush()
            // for throughput test e.g
            //    $ dd if=/dev/zero of=/dev/ttyACM0 count=10000
            for(uint32_t i = 0; i < count; i++)
            {
                if(buf[i] == '\r')
                    tud_cdc_write("\r\n", 2);
                else if((buf[i] == '\b') || (buf[i] == 0x7f))
                    tud_cdc_write("\b\033[K", 4); // Clear the deleted character
                else
                    tud_cdc_write_char(buf[i]);
            }
            tud_cdc_write_flush();
        }
    }
}

/* USER CODE BEGIN 1 */
int __io_putchar(int ch)
{
    /* write a character to USB */
    tud_cdc_write_char(ch);
    tud_cdc_write_flush();

    return ch;
}

void write_string(char *s)
{
    int len = strlen(s);
    for (int i = 0; i < len; i++)
        __io_putchar(s[i]);
}

void write_int(uint32_t n)
{
    uint8_t leading_zeros = 1;
    for(int i = 28; i >= 0; i -= 4)
    {
        char c = (n >> i) & 0xF;
        if (c <= 9)
            c += 0x30;
        else
            c += 55;

        // Skip leading zeros
        if ((c != '0' && leading_zeros == 1) || (i == 0))
            leading_zeros = 0;

        if(leading_zeros == 0)
            __io_putchar(c);
    }
}

/* Blocks until user enters a value, then returns that value */
long read_int()
{
    long value;

    /* Wait for enter key to be pressed */
    while((rx_counter == 0) || (rx_buffer[rx_counter - 1] != '\r'));
    rx_buffer[rx_counter - 1] = '\0';

    /* Get the entered value and convert to integer */
    value = strtol((char*)rx_buffer, NULL, 0);

    /* Reset the rx_counter */
    rx_counter = 0;

    return value;
}

/* Blocks until user enters a value, then returns that value */
long read_hex()
{
    long value;

    /* Wait for enter key to be pressed */
    while((rx_counter == 0) || (rx_buffer[rx_counter - 1] != '\r'));
    rx_buffer[rx_counter - 1] = '\0';

    /* Get the entered value and convert to integer */
    value = strtol((char*)rx_buffer, NULL, 16);

    /* Reset the rx_counter */
    rx_counter = 0;

    return value;
}

/* Blocks until the user enters a character */
char read_char()
{
    char c;

    /* Wait for the enter key to be pressed */
    while((rx_counter == 0) || (rx_buffer[rx_counter - 1] != '\r'));
    rx_buffer[rx_counter - 1] = '\0';

    /* Return the first character entered, ignore the rest */
    c = rx_buffer[0];

    /* Reset the rx_counter */
    rx_counter = 0;

    return c;
}


void USB_OTG1_IRQHandler(void)
{
    tud_int_handler(0);
}

