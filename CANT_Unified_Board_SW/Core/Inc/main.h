/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED_ACT1_Pin GPIO_PIN_4
#define LED_ACT1_GPIO_Port GPIOC
#define LED_ACT2_Pin GPIO_PIN_5
#define LED_ACT2_GPIO_Port GPIOC
#define LED_PWR_Pin GPIO_PIN_2
#define LED_PWR_GPIO_Port GPIOB
#define MODE8_Pin GPIO_PIN_8
#define MODE8_GPIO_Port GPIOE
#define MODE7_Pin GPIO_PIN_9
#define MODE7_GPIO_Port GPIOE
#define MODE6_Pin GPIO_PIN_10
#define MODE6_GPIO_Port GPIOE
#define MODE5_Pin GPIO_PIN_11
#define MODE5_GPIO_Port GPIOE
#define MODE4_Pin GPIO_PIN_12
#define MODE4_GPIO_Port GPIOE
#define MODE3_Pin GPIO_PIN_13
#define MODE3_GPIO_Port GPIOE
#define MODE2_Pin GPIO_PIN_14
#define MODE2_GPIO_Port GPIOE
#define MODE1_Pin GPIO_PIN_15
#define MODE1_GPIO_Port GPIOE
#define CAN3_SHORT_Pin GPIO_PIN_6
#define CAN3_SHORT_GPIO_Port GPIOB
#define CAN1_SHORT_Pin GPIO_PIN_7
#define CAN1_SHORT_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
