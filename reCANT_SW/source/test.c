#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "test.h"
#include "usb.h"
#include "tusb.h"
#include "fsl_gpio.h"
#include "fsl_iomuxc.h"
#include "pin_mux.h"

void runTestProgram()
{
    // Reconfigure all pins as GPIO
    IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_02_GPIO1_IO02, 0U); //FLEXCAN2_TX
    IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_03_GPIO1_IO03, 0U); //FLEXCAN2_RX
    IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_08_GPIO1_IO24, 0U); //FLEXCAN1_TX
    IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_09_GPIO1_IO25, 0U); //FLEXCAN1_RX
    IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_36_GPIO3_IO22, 0U);   //FLEXCAN3_TX
    IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_37_GPIO3_IO23, 0U);   //FLEXCAN3_RX
    IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_31_GPIO4_IO31, 0U);   //UART7_TX
    IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_32_GPIO3_IO18, 0U);   //UART7_RX

    while(! tud_cdc_connected() );
    write_string("Start Test? (Y/n)\r\n");
    while(1)
    {
        char input = read_char();
        if(input == 'Y' || input == 'y')
            break;
    }
    write_string("Test Started\r\n");
    write_string("Testing LEDS\r\n");

    write_string("Turning PWR LED on\r\n");
    GPIO_PinWrite(BOARD_INITPINS_PWR_LED_PORT, BOARD_INITPINS_PWR_LED_PIN, 1);
    write_string("PWR LED should be on. Press Enter to Continue");
    read_char();
    GPIO_PinWrite(BOARD_INITPINS_PWR_LED_PORT, BOARD_INITPINS_PWR_LED_PIN, 0);
    write_string("Turning PWR LED off\r\n\r\n");

    write_string("Turning CAN1 LED on\r\n");
    GPIO_PinWrite(BOARD_INITPINS_CAN1_LED_PORT, BOARD_INITPINS_CAN1_LED_PIN, 1);
    write_string("CAN1 LED should be on. Press Enter to Continue");
    read_char();
    GPIO_PinWrite(BOARD_INITPINS_CAN1_LED_PORT, BOARD_INITPINS_CAN1_LED_PIN, 0);
    write_string("Turning CAN1 LED off\r\n\r\n");

    write_string("Turning CAN2 LED on\r\n");
    GPIO_PinWrite(BOARD_INITPINS_CAN2_LED_PORT, BOARD_INITPINS_CAN2_LED_PIN, 1);
    write_string("CAN2 LED should be on. Press Enter to Continue");
    read_char();
    GPIO_PinWrite(BOARD_INITPINS_CAN2_LED_PORT, BOARD_INITPINS_CAN2_LED_PIN, 0);
    write_string("Turning CAN2 LED off\r\n\r\n");

    write_string("Turning CAN3 LED on\r\n");
    GPIO_PinWrite(BOARD_INITPINS_CAN3_LED_PORT, BOARD_INITPINS_CAN3_LED_PIN, 1);
    write_string("CAN3 LED should be on. Press Enter to Continue");
    read_char();
    GPIO_PinWrite(BOARD_INITPINS_CAN3_LED_PORT, BOARD_INITPINS_CAN3_LED_PIN, 0);
    write_string("Turning CAN3 LED off\r\n\r\n");

    write_string("Testing CANT Shorting Switches and termination resistors\r\n");

    
    GPIO_PinWrite(BOARD_INITPINS_CAN1_SW_PORT, BOARD_INITPINS_CAN1_SW_PIN, 1);
    write_string("Testing CAN1 shorting switch. Check resistance between CAN1+ and CAN1-. Resistance should be between 6 and 8 ohms. Press Enter to Contine\r\n");
    read_char();
    GPIO_PinWrite(BOARD_INITPINS_CAN1_SW_PORT, BOARD_INITPINS_CAN1_SW_PIN, 0);
    write_string("Shorting switch off. Check resistance between CAN1+ and CAN1-. Resistance should be approcimately 120 ohms if the termination resistor jumper is on, and several megaOhms if the jumper is off. Press Enter to Contine\r\n");
    read_char();

    GPIO_PinWrite(BOARD_INITPINS_CAN2_SW_PORT, BOARD_INITPINS_CAN2_SW_PIN, 1);
    write_string("Testing CAN2 shorting switch. Check resistance between CAN2+ and CAN2-. Resistance should be between 6 and 8 ohms. Press Enter to Contine\r\n");
    read_char();
    GPIO_PinWrite(BOARD_INITPINS_CAN2_SW_PORT, BOARD_INITPINS_CAN2_SW_PIN, 0);
    write_string("Shorting switch off. Check resistance between CAN2+ and CAN2-. Resistance should be approcimately 120 ohms if the termination resistor jumper is on, and several megaOhms if the jumper is off. Press Enter to Contine\r\n");
    read_char();

    GPIO_PinWrite(BOARD_INITPINS_CAN3_SW_PORT, BOARD_INITPINS_CAN3_SW_PIN, 1);
    write_string("Testing CAN3 shorting switch. Check resistance between CAN3+ and CAN3-. Resistance should be between 6 and 8 ohms. Press Enter to Contine\r\n");
    read_char();
    GPIO_PinWrite(BOARD_INITPINS_CAN3_SW_PORT, BOARD_INITPINS_CAN3_SW_PIN, 0);
    write_string("Shorting switch off. Check resistance between CAN3+ and CAN3-. Resistance should be approcimately 120 ohms if the termination resistor jumper is on, and several megaOhms if the jumper is off. Press Enter to Contine\r\n");
    read_char();

    write_string("Testing CAN TX functionality\r\n");

    GPIO_PinWrite(GPIO1, 24, 1);
    write_string("Testing CAN1 TX. CAN1+ should be approximately 3.5v and CAN1- should be approximately 1.5v. Press Enter to Continue\r\n");
    read_char();
    GPIO_PinWrite(GPIO1, 24, 0);
    write_string("Testing CAN1 TX. CAN1+ should be approximately 2.5v and CAN1- should be approximately 2.5v. Press Enter to Continue\r\n");
    read_char();

    GPIO_PinWrite(GPIO1, 2, 1);
    write_string("Testing CAN2 TX. CAN2+ should be approximately 3.5v and CAN2- should be approximately 1.5v. Press Enter to Continue\r\n");
    read_char();
    GPIO_PinWrite(GPIO1, 2, 0);
    write_string("Testing CAN2 TX. CAN2+ should be approximately 2.5v and CAN2- should be approximately 2.5v. Press Enter to Continue\r\n");
    read_char();

    GPIO_PinWrite(GPIO3, 22, 1);
    write_string("Testing CAN3 TX. CAN3+ should be approximately 3.5v and CAN3- should be approximately 1.5v. Press Enter to Continue\r\n");
    read_char();
    GPIO_PinWrite(GPIO3, 22, 0);
    write_string("Testing CAN3 TX. CAN3+ should be approximately 2.5v and CAN3- should be approximately 2.5v. Press Enter to Continue\r\n");
    read_char();

    write_string("\r\nTest Complete. TODO: CAN RX functionality and J1708 Functionality do not currently have tests.\r\n");
}

