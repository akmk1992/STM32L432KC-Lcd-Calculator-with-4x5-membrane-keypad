/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#include "stm32l4xx_hal.h"

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
#define MCO_Pin GPIO_PIN_0
#define MCO_GPIO_Port GPIOA
#define VCP_TX_Pin GPIO_PIN_2
#define VCP_TX_GPIO_Port GPIOA
#define ROW1_OUTPUT_Pin GPIO_PIN_3
#define ROW1_OUTPUT_GPIO_Port GPIOA
#define ROW2_OUTPUT_Pin GPIO_PIN_4
#define ROW2_OUTPUT_GPIO_Port GPIOA
#define ROW3_OUTPUT_Pin GPIO_PIN_5
#define ROW3_OUTPUT_GPIO_Port GPIOA
#define COL1_INPUT_Pin GPIO_PIN_0
#define COL1_INPUT_GPIO_Port GPIOB
#define COL4_INPUT_Pin GPIO_PIN_1
#define COL4_INPUT_GPIO_Port GPIOB
#define SWDIO_Pin GPIO_PIN_13
#define SWDIO_GPIO_Port GPIOA
#define SWCLK_Pin GPIO_PIN_14
#define SWCLK_GPIO_Port GPIOA
#define VCP_RX_Pin GPIO_PIN_15
#define VCP_RX_GPIO_Port GPIOA
#define LD3_Pin GPIO_PIN_3
#define LD3_GPIO_Port GPIOB
#define ROW4_OUPUT_Pin GPIO_PIN_4
#define ROW4_OUPUT_GPIO_Port GPIOB
#define ROW5_OUTPUT_Pin GPIO_PIN_5
#define ROW5_OUTPUT_GPIO_Port GPIOB
#define COL3_INPUT_Pin GPIO_PIN_6
#define COL3_INPUT_GPIO_Port GPIOB
#define COL2_INPUT_Pin GPIO_PIN_7
#define COL2_INPUT_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
