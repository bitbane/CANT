#include "pin_mux.h"
#include "fsl_gpio.h"
#include "led.h"

void PWR_LED_Toggle()
{
    if((BOARD_INITPINS_PWR_LED_PORT->DR | BOARD_INITPINS_PWR_LED_PIN_MASK) > 0)
        PWR_LED_Off;
    else
        PWR_LED_On;
}

void CAN1_LED_Toggle()
{
    if((BOARD_INITPINS_CAN1_LED_PORT->DR | BOARD_INITPINS_CAN1_LED_PIN_MASK) > 0)
        CAN1_LED_Off;
    else
        CAN1_LED_On;
}

void CAN2_LED_Toggle()
{
    if((BOARD_INITPINS_CAN2_LED_PORT->DR | BOARD_INITPINS_CAN2_LED_PIN_MASK) > 0)
        CAN2_LED_Off;
    else
        CAN2_LED_On;
}

void CAN3_LED_Toggle()
{
    if((BOARD_INITPINS_CAN3_LED_PORT->DR | BOARD_INITPINS_CAN3_LED_PIN_MASK) > 0)
        CAN3_LED_Off;
    else
        CAN3_LED_On;
}

