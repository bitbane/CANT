/*
 * Copyright (c) 2022 - 2022, Tim Brom
 */

#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "clock_config.h"

#include "usb_device_config.h"
#include "usb.h"
#include "usb_device.h"
#include "usb_phy.h"
#include "peripherals.h"
#include "pin_mux.h"

#define CONTROLLER_ID 2u

/*!
 * @brief Main function
 */
int main(void)
{
    char ch;

    /* Init board hardware. */
    BOARD_InitBootPeripherals();
    BOARD_InitBootClocks();
    BOARD_InitBootPins();
    DbgConsole_Init((uint8_t)CONTROLLER_ID, (uint32_t)NULL, kSerialPort_UsbCdc, (uint32_t)NULL);

    PRINTF("hello world.\r\n");

    while (1)
    {
        ch = GETCHAR();
        PUTCHAR(ch);
    }
}
