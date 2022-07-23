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

    // Set 1ms system tick
    SysTick_Config(SystemCoreClock / 1000);

    while (1)
    {
    }
}

volatile uint32_t system_ticks = 0;
void SysTick_Handler(void)
{
    if((system_ticks & 0x00000FFF) == 0x800)
        GPIO_PinWrite(BOARD_INITPINS_TEENSY_LED_PORT, BOARD_INITPINS_TEENSY_LED_PIN, 1);
    else if ((system_ticks & 0x00000FFF) == 0x000)
        GPIO_PinWrite(BOARD_INITPINS_TEENSY_LED_PORT, BOARD_INITPINS_TEENSY_LED_PIN, 0);
    system_ticks++;
}
