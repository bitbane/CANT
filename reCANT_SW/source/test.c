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
    // FLEXCAN1_TX AD_B1_08 H13
    // FLEXCAN1_RX AD_B1_09 M13
    // FLEXCAN2_TX AD_B0_02 M11
    // FLEXCAN2_RX AD_B0_03 O11
    // FLEXCAN3_TX EMC_36 C3
    // FLEXCAN3_RX EMC_37 E4
    // UART7_TX EMC_31 C5
    // UART7_RX EMC_32 D5
    //
    
    /* GPIO Output Configuration */
    gpio_pin_config_t Output_config = {
        .direction = kGPIO_DigitalOutput,
        .outputLogic = 0U,
        .interruptMode = kGPIO_NoIntmode
    };
    /* Initialize GPIO functionality on GPIO_AD_B1_08 (pin H13) */
    GPIO_PinInit(GPIO1, 24U, &Output_config);
    IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_08_GPIO1_IO24, 0U); 
    IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B1_08_GPIO1_IO24, 0x30B0U); 

    /* Initialize GPIO functionality on GPIO_AD_B0_02 (pin M11) */
    GPIO_PinInit(GPIO1, 2U, &Output_config);
    IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_02_GPIO1_IO02, 0U); 
    IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B0_02_GPIO1_IO02, 0x30B0U); 

    /* Initialize GPIO functionality on GPIO_EMC_36 (pin C3) */
    GPIO_PinInit(GPIO3, 22U, &Output_config);
    IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_36_GPIO3_IO22, 0U); 
    IOMUXC_SetPinConfig(IOMUXC_GPIO_EMC_36_GPIO3_IO22, 0x30B0U); 

    /* Initialize GPIO functionality on GPIO_EMC31 (pin C5) */
    GPIO_PinInit(GPIO4, 31U, &Output_config);
    IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_31_GPIO4_IO31, 0U); 
    IOMUXC_SetPinConfig(IOMUXC_GPIO_EMC_31_GPIO4_IO31, 0x30B0U); 



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

    GPIO_PinWrite(GPIO4, 31, 1);
    write_string("J1708 TX line is high. Should read TODO from J1708 connector. Press Enter to Contine\r\n");
    read_char();
    GPIO_PinWrite(GPIO4, 31, 0);
    write_string("J1708 TX line is low. Should read TODO from J1708 connector. Press Enter to Contine\r\n");
    read_char();
    

    write_string("\r\nTest Complete. TODO: CAN RX functionality and J1708 RX Functionality do not currently have tests.\r\n");
}

