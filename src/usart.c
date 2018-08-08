/**
  ******************************************************************************
  * File Name          : USART.c
  * Description        : This file provides code for the configuration
  *                      of the USART instances.
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2017 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include <stdlib.h>
#include "usart.h"

#include "gpio.h"

/* USER CODE BEGIN 0 */
volatile uint8_t rx_buffer[RX_BUFFER_SIZE];
volatile uint8_t rx_counter = 0;

/* USER CODE END 0 */

UART_HandleTypeDef huart3;

/* USART3 init function */

void MX_USART3_UART_Init(void)
{

  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  huart3.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart3.Init.Prescaler = UART_PRESCALER_DIV1;
  huart3.Init.FIFOMode = UART_FIFOMODE_DISABLE;
  huart3.Init.TXFIFOThreshold = UART_TXFIFO_THRESHOLD_1_8;
  huart3.Init.RXFIFOThreshold = UART_RXFIFO_THRESHOLD_1_8;
  huart3.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
  }

}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  if(uartHandle->Instance==USART3)
  {
  /* USER CODE BEGIN USART3_MspInit 0 */

  /* USER CODE END USART3_MspInit 0 */
    /* USART3 clock enable */
    __HAL_RCC_USART3_CLK_ENABLE();
  
    /**USART3 GPIO Configuration    
    PD8     ------> USART3_TX
    PD9     ------> USART3_RX 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART3;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    /* USART3 interrupt Init */
    HAL_NVIC_SetPriority(USART3_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART3_IRQn);
    
    /* Enable the RX interrupt */
    SET_BIT(USART3->CR1, USART_CR1_RXNEIE);
  /* USER CODE BEGIN USART3_MspInit 1 */

  /* USER CODE END USART3_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==USART3)
  {
  /* USER CODE BEGIN USART3_MspDeInit 0 */

  /* USER CODE END USART3_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART3_CLK_DISABLE();
  
    /**USART3 GPIO Configuration    
    PD8     ------> USART3_TX
    PD9     ------> USART3_RX 
    */
    HAL_GPIO_DeInit(GPIOD, GPIO_PIN_8|GPIO_PIN_9);

    /* USART3 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART3_IRQn);
  /* USER CODE BEGIN USART3_MspDeInit 1 */

  /* USER CODE END USART3_MspDeInit 1 */
  }
} 

/* USER CODE BEGIN 1 */
int __io_putchar(int ch)
{
    /* Wait for previous TX to complete */
    while((USART3->ISR & UART_FLAG_TXE) == 0);

    /* write a character to the USART */
    USART3->TDR = (uint8_t)(ch & 0xFF);

    return ch;
}

void write_string(char *s)
{
    int len = strlen(s);
    for (int i = 0; i < len; i++)
        __io_putchar(s[i]);
}

void write_int(uint32_t n)
{
    uint8_t leading_zeros = 1;
    for(int i = 28; i >= 0; i -= 4)
    {
        char c = (n >> i) & 0xF;
        if (c <= 9)
            c += 0x30;
        else
            c += 55;

        // Skip leading zeros
        if ((c != '0' && leading_zeros == 1) || (i == 0))
            leading_zeros = 0;

        if(leading_zeros == 0)
            __io_putchar(c);
    }
}

/* Blocks until user enters a value, then returns that value */
long read_int()
{
    long value;

    /* Wait for enter key to be pressed */
    while((rx_counter == 0) || (rx_buffer[rx_counter - 1] != '\r'));
    rx_buffer[rx_counter - 1] = '\0';

    /* Get the entered value and convert to integer */
    value = strtol((char*)rx_buffer, NULL, 0);

    /* Disable the interrupt, reset the rx_counter */
    CLEAR_BIT(USART3->CR1, USART_CR1_RXNEIE);
    rx_counter = 0;
    SET_BIT(USART3->CR1, USART_CR1_RXNEIE);

    return value;
}

/* Blocks until user enters a value, then returns that value */
long read_hex()
{
    long value;

    /* Wait for enter key to be pressed */
    while((rx_counter == 0) || (rx_buffer[rx_counter - 1] != '\r'));
    rx_buffer[rx_counter - 1] = '\0';

    /* Get the entered value and convert to integer */
    value = strtol((char*)rx_buffer, NULL, 16);

    /* Disable the interrupt, reset the rx_counter */
    CLEAR_BIT(USART3->CR1, USART_CR1_RXNEIE);
    rx_counter = 0;
    SET_BIT(USART3->CR1, USART_CR1_RXNEIE);

    return value;
}

/* Blocks until the user enters a character */
char read_char()
{
    char c;

    /* Wait for the enter key to be pressed */
    while((rx_counter == 0) || (rx_buffer[rx_counter - 1] != '\r'));
    rx_buffer[rx_counter - 1] = '\0';

    /* Return the first character entered, ignore the rest */
    c = rx_buffer[0];

    /* Disable the interrupt, reset the rx_counter */
    CLEAR_BIT(USART3->CR1, USART_CR1_RXNEIE);
    rx_counter = 0;
    SET_BIT(USART3->CR1, USART_CR1_RXNEIE);

    return c;
}

/**
 * @brief This function handles the USART3 IRQ Handler 
 */
void USART3_IRQHandler(void)
{
    if((USART3->ISR & USART_ISR_RXNE) != RESET)
    {
        /* Read one byte from the receive data register */
        rx_buffer[rx_counter] = USART3->RDR & 0x1FF;
        if(rx_buffer[rx_counter] == '\r')
        {
            __io_putchar('\r');
            __io_putchar('\n');
        }
        // Backspace or delete character
        else if((rx_buffer[rx_counter] == '\b' || rx_buffer[rx_counter] == 0x7f) && rx_counter > 0)
        {
            rx_counter -= 2;
            write_string("\b\033[K"); // Clear the deleted character
        }
        else
        {
            __io_putchar(rx_buffer[rx_counter]);
        }

        rx_counter++;
        if(rx_counter == RX_BUFFER_SIZE)
        {
            /* Disable the UART 4 Receive interrupt */
            CLEAR_BIT(USART3->CR1, USART_CR1_RXNEIE);
        }
    }
}

/* USER CODE END 1 */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
