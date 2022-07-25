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

uint32_t num_flashes = 1;

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
        num_flashes = 1;
    }
    else if(GPIO_PinRead(BOARD_INITPINS_RUN_CANT_PORT, BOARD_INITPINS_RUN_CANT_PIN))
    {
        strcpy(program, "CANT\r\n");
        num_flashes = 2;
    }
    else if(GPIO_PinRead(BOARD_INITPINS_RUN_SOCKETCAN_PORT, BOARD_INITPINS_RUN_SOCKETCAN_PIN))
    {
        strcpy(program, "SocketCAN\r\n");
        num_flashes = 3;
    }
    else if(GPIO_PinRead(BOARD_INITPINS_RUN_TRUCKDEVIL_PORT, BOARD_INITPINS_RUN_TRUCKDEVIL_PIN))
    {
        strcpy(program, "TruckDevil\r\n");
        num_flashes = 4;
    }
    else if(GPIO_PinRead(BOARD_INITPINS_RUN_SW5_PORT, BOARD_INITPINS_RUN_SW5_PIN))
    {
        strcpy(program, "SW5\r\n");
        num_flashes = 5;
    }
    else if(GPIO_PinRead(BOARD_INITPINS_RUN_SW6_PORT, BOARD_INITPINS_RUN_SW6_PIN))
    {
        strcpy(program, "SW6\r\n");
        num_flashes = 6;
    }
    else if(GPIO_PinRead(BOARD_INITPINS_RUN_SW7_PORT, BOARD_INITPINS_RUN_SW7_PIN))
    {
        strcpy(program, "SW7\r\n");
        num_flashes = 7;
    }
    else
    {
        strcpy(program, "TEST\r\n");
        num_flashes = UINT32_MAX;
        runTestProgram();
    }

    while (1)
    {
    }
}

/* Interrupts */
volatile uint32_t system_ticks = 0;
volatile uint32_t flash_count = 0;
void SysTick_Handler(void)
{
    if((system_ticks & 0x000001FF) == 0x100)
    {
        flash_count++;
        if(flash_count <= num_flashes)
            GPIO_PinWrite(BOARD_INITPINS_TEENSY_LED_PORT, BOARD_INITPINS_TEENSY_LED_PIN, 1);
        else
            flash_count = 0;
    }
    else if ((system_ticks & 0x000001FF) == 0x000)
        GPIO_PinWrite(BOARD_INITPINS_TEENSY_LED_PORT, BOARD_INITPINS_TEENSY_LED_PIN, 0);
    system_ticks++;
    tud_task();
    usb_serial_task();
}

 
