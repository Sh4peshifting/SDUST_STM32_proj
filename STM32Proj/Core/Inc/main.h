/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "stm32f1xx_hal.h"

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
#define CO_AO_Pin GPIO_PIN_0
#define CO_AO_GPIO_Port GPIOA
#define GUARD_Pin GPIO_PIN_1
#define GUARD_GPIO_Port GPIOA
#define light_AO_Pin GPIO_PIN_2
#define light_AO_GPIO_Port GPIOA
#define light_DO_Pin GPIO_PIN_3
#define light_DO_GPIO_Port GPIOA
#define CO_DO_Pin GPIO_PIN_0
#define CO_DO_GPIO_Port GPIOB
#define AUDIO_TX_Pin GPIO_PIN_10
#define AUDIO_TX_GPIO_Port GPIOB
#define AUDIO_RX_Pin GPIO_PIN_11
#define AUDIO_RX_GPIO_Port GPIOB
#define BUZZER2_Pin GPIO_PIN_3
#define BUZZER2_GPIO_Port GPIOG
#define BUZZER1_Pin GPIO_PIN_4
#define BUZZER1_GPIO_Port GPIOG
#define LED3_Pin GPIO_PIN_5
#define LED3_GPIO_Port GPIOG
#define LED2_Pin GPIO_PIN_6
#define LED2_GPIO_Port GPIOG
#define LED1_Pin GPIO_PIN_7
#define LED1_GPIO_Port GPIOG
#define DISP_TX_Pin GPIO_PIN_9
#define DISP_TX_GPIO_Port GPIOA
#define DISP_RX_Pin GPIO_PIN_10
#define DISP_RX_GPIO_Port GPIOA
#define AIR_TX_Pin GPIO_PIN_10
#define AIR_TX_GPIO_Port GPIOC
#define AIR_RX_Pin GPIO_PIN_11
#define AIR_RX_GPIO_Port GPIOC
#define VISUAL_TX_Pin GPIO_PIN_12
#define VISUAL_TX_GPIO_Port GPIOC
#define VISUAL_RX_Pin GPIO_PIN_2
#define VISUAL_RX_GPIO_Port GPIOD
#define BLUETOOTH_TX_Pin GPIO_PIN_5
#define BLUETOOTH_TX_GPIO_Port GPIOD
#define BLUETOOTH_RX_Pin GPIO_PIN_6
#define BLUETOOTH_RX_GPIO_Port GPIOD
#define TB6612_SETY_Pin GPIO_PIN_10
#define TB6612_SETY_GPIO_Port GPIOG
#define TB6612_GPIO1_Pin GPIO_PIN_11
#define TB6612_GPIO1_GPIO_Port GPIOG
#define TB6612_GPIO2_Pin GPIO_PIN_12
#define TB6612_GPIO2_GPIO_Port GPIOG
#define TB6612_GPIO3_Pin GPIO_PIN_13
#define TB6612_GPIO3_GPIO_Port GPIOG
#define TB6612_GPIO4_Pin GPIO_PIN_14
#define TB6612_GPIO4_GPIO_Port GPIOG
#define TB6612_MOTOR_Pin GPIO_PIN_5
#define TB6612_MOTOR_GPIO_Port GPIOB
#define TB6612_FAN_Pin GPIO_PIN_7
#define TB6612_FAN_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
