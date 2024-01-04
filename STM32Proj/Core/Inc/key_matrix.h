#ifndef __KEY_MATRIX_H
#define __KEY_MATRIX_H

#include "main.h"                  
#include "cmsis_os.h"
#include "FreeRTOS.h"
#include "uart_web_proc.h"

#define C1_ON HAL_GPIO_WritePin(GPIOF, GPIO_PIN_0, GPIO_PIN_SET) 
#define C1_OFF HAL_GPIO_WritePin(GPIOF, GPIO_PIN_0, GPIO_PIN_RESET) 

#define C2_ON HAL_GPIO_WritePin(GPIOF, GPIO_PIN_2, GPIO_PIN_SET) 
#define C2_OFF HAL_GPIO_WritePin(GPIOF, GPIO_PIN_2, GPIO_PIN_RESET) 

#define C3_ON HAL_GPIO_WritePin(GPIOF, GPIO_PIN_4, GPIO_PIN_SET) 
#define C3_OFF HAL_GPIO_WritePin(GPIOF, GPIO_PIN_4, GPIO_PIN_RESET) 

#define C4_ON HAL_GPIO_WritePin(GPIOF, GPIO_PIN_6, GPIO_PIN_SET) 
#define C4_OFF HAL_GPIO_WritePin(GPIOF, GPIO_PIN_6, GPIO_PIN_RESET) 


#define R1_Read HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_1)
#define R2_Read HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_3)

#define R3_Read HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_5)
#define R4_Read HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_7)

extern uint8_t lockState;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;

void password_check(void);
unsigned char MatrixKey(void);
#endif


