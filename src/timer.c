#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_tim.h"
#include <stdio.h>
#include "timer.h"
#include <stdbool.h>

void (*timer_callback_handler)(void) = NULL;

/* Sets up an interval timer on TIM3 */
void timer_init(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_InitStructure; 
    GPIO_InitTypeDef GPIO_InitStructure;

    /* Enable TIM3 clock */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

    /* LED */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    /* Set up the interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* Set up the TIM3 peripheral */
    TIM_InitStructure.TIM_ClockDivision = TIM_CKD_DIV4;
    TIM_InitStructure.TIM_Prescaler = 41999; /* APB1 clock is at 42 MHz, and this timer counts at twice that speed. Count every 1/2 millisecond. Note: The prescale value used is the register value + 1 */
    TIM_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_InitStructure.TIM_Period = 1000; /* Start with one second */

    TIM_TimeBaseInit(TIM3, &TIM_InitStructure);

    timer_callback_handler = NULL;
}

void timer_startInterval(void (*p_timer_callback_handler)(void), uint16_t period_ms)
{
    TIM_SetAutoreload(TIM3, period_ms);
    TIM_SetCounter(TIM3, 0);
    timer_callback_handler = *p_timer_callback_handler;

    TIM_Cmd(TIM3, ENABLE);

    /* Enable the overflow interrupt */
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
}

void timer_stopInterval()
{
    TIM_Cmd(TIM3, DISABLE);

    /* Disable the overflow interrupt */
    TIM_ITConfig(TIM3, TIM_IT_Update, DISABLE);

    /* Disable the callback */
    timer_callback_handler = NULL;
}

void timer_toggleLed()
{
    static bool turned_on = false;

    if(turned_on)
    {
        GPIOD->ODR &= ~GPIO_Pin_12;
    }
    else
    {
        GPIOD->ODR |= GPIO_Pin_12;
    }

    turned_on = !turned_on;
}

void TIM3_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
    {
        TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
        timer_toggleLed();
        if(timer_callback_handler != NULL)
        {
            timer_callback_handler();
        }
    }
}

