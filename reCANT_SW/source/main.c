/*
 * Copyright (c) 2022 - 2022, Tim Brom
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "fsl_device_registers.h"
#include "clock_config.h"

#include "peripherals.h"
#include "pin_mux.h"

/*!
 * @brief Main function
 */
int main(void)
{
    /* Init board hardware. */
    BOARD_InitBootClocks();
    SystemCoreClockUpdate();
    BOARD_InitBootPins();
    BOARD_InitBootPeripherals();
    uint32_t count = 0;

    while (1)
    {
        count++;

        if(count == 200000000)
            GPIO_PinWrite(BOARD_INITPINS_TEENSY_LED_PORT, BOARD_INITPINS_TEENSY_LED_PIN, 0);

        if(count >= 400000000)
        {
            GPIO_PinWrite(BOARD_INITPINS_TEENSY_LED_PORT, BOARD_INITPINS_TEENSY_LED_PIN, 1);
            count = 0;
        }
    }
}
