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

#include "tusb.h"
#include "usb.h"
#include "test.h"


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
    USB_Init();

    tud_init(BOARD_TUD_RHPORT);

    // Set 1ms system tick
    SysTick_Config(SystemCoreClock / 1000);
    char program[16];

    // What program are we running?
    if(GPIO_PinRead(BOARD_INITPINS_RUN_CANCAT_PORT, BOARD_INITPINS_RUN_CANCAT_PIN))
    {
        strcpy(program, "CanCat\r\n");
    }
    else if(GPIO_PinRead(BOARD_INITPINS_RUN_CANT_PORT, BOARD_INITPINS_RUN_CANT_PIN))
    {
        strcpy(program, "CANT\r\n");
    }
    else if(GPIO_PinRead(BOARD_INITPINS_RUN_SOCKETCAN_PORT, BOARD_INITPINS_RUN_SOCKETCAN_PIN))
    {
        strcpy(program, "SocketCAN\r\n");
    }
    else if(GPIO_PinRead(BOARD_INITPINS_RUN_TRUCKDEVIL_PORT, BOARD_INITPINS_RUN_TRUCKDEVIL_PIN))
    {
        strcpy(program, "TruckDevil\r\n");
    }
    else if(GPIO_PinRead(BOARD_INITPINS_RUN_SW5_PORT, BOARD_INITPINS_RUN_SW5_PIN))
    {
        strcpy(program, "SW5\r\n");
    }
    else if(GPIO_PinRead(BOARD_INITPINS_RUN_SW6_PORT, BOARD_INITPINS_RUN_SW6_PIN))
    {
        strcpy(program, "SW6\r\n");
    }
    else if(GPIO_PinRead(BOARD_INITPINS_RUN_SW7_PORT, BOARD_INITPINS_RUN_SW7_PIN))
    {
        strcpy(program, "SW7\r\n");
    }
    else
    {
        strcpy(program, "TEST\r\n");
        runTestProgram();
    }


    while (1)
    {
    }
}

/* Interrupts */
volatile uint32_t system_ticks = 0;
void SysTick_Handler(void)
{
    if((system_ticks & 0x00000FFF) == 0x800)
        GPIO_PinWrite(BOARD_INITPINS_TEENSY_LED_PORT, BOARD_INITPINS_TEENSY_LED_PIN, 1);
    else if ((system_ticks & 0x00000FFF) == 0x000)
        GPIO_PinWrite(BOARD_INITPINS_TEENSY_LED_PORT, BOARD_INITPINS_TEENSY_LED_PIN, 0);
    system_ticks++;
    tud_task();
    usb_serial_task();
}

 
