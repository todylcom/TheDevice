/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021 STMicroelectronics.
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
#include "stm32l0xx_hal.h"

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
#define LETT_L_Pin GPIO_PIN_1
#define LETT_L_GPIO_Port GPIOA
#define LETT_Y_Pin GPIO_PIN_3
#define LETT_Y_GPIO_Port GPIOA
#define LETT_D_Pin GPIO_PIN_4
#define LETT_D_GPIO_Port GPIOA
#define LETT_O_Pin GPIO_PIN_5
#define LETT_O_GPIO_Port GPIOA
#define LETT_T_Pin GPIO_PIN_6
#define LETT_T_GPIO_Port GPIOA
#define LOGO_Pin GPIO_PIN_7
#define LOGO_GPIO_Port GPIOA
#define LIGHT_PWR_Pin GPIO_PIN_1
#define LIGHT_PWR_GPIO_Port GPIOB
#define BUTTON_Pin GPIO_PIN_8
#define BUTTON_GPIO_Port GPIOA
#define BUTTON_EXTI_IRQn EXTI4_15_IRQn
#define BATT_CHRG_Pin GPIO_PIN_6
#define BATT_CHRG_GPIO_Port GPIOB
#define BATT_CHRG_EXTI_IRQn EXTI4_15_IRQn
#define BATT_STDBY_Pin GPIO_PIN_7
#define BATT_STDBY_GPIO_Port GPIOB
#define BATT_STDBY_EXTI_IRQn EXTI4_15_IRQn
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
