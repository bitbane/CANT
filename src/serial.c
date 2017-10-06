#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "misc.h"
#include <stdio.h>
#include <unistd.h>
#include "serial.h"

uint8_t Rx_Buffer[RXBUFFERSIZE];
__IO uint16_t Rx_Counter = 0;

/* Sets up a serial channel an PA0 and PA1 */
void serial_init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    USART_InitTypeDef UART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

    /* Set up the interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* Enable UART clock */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);

    /* GPIO Pin Config */
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_UART4);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_UART4);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* UART4 Config */
    UART_InitStructure.USART_BaudRate = 115200;
    UART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    UART_InitStructure.USART_StopBits = USART_StopBits_1;
    UART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    UART_InitStructure.USART_Parity = USART_Parity_No;
    UART_InitStructure.USART_WordLength = USART_WordLength_8b;

    USART_Init(UART4, &UART_InitStructure);

    USART_Cmd(UART4, ENABLE);

    /* Enable the RX interrupt */
    USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);
}

int __io_putchar(int ch)
{
    /* e.g. write a character to the USART */
    USART_SendData(UART4, (uint8_t) ch);

    /* Loop until the end of transmission */
    while (USART_GetFlagStatus(UART4, USART_FLAG_TC) == RESET)
    {}

    return ch;
}


