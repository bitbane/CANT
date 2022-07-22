/*
 * Copyright (c) 2022 - 2022, Tim Brom
 */

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
    BOARD_InitBootPeripherals();
    BOARD_InitBootClocks();
    BOARD_InitBootPins();

    while (1)
    {
    }
}
