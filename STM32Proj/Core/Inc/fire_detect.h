#ifndef __FIRE_DETECT_H
#define __FIRE_DETECT_H

#include "stm32f1xx_hal.h"
#include "uart_web_proc.h"

#define gas_Seneor_Do HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0)
#define human_detectrion_flag HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1)

uint8_t Fire_Human_System(uint8_t temp);

#endif

