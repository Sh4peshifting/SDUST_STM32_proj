#ifndef __UART_VISUAL_PROC_H__
#define __UART_VISUAL_PROC_H__

#include "main.h"
#include "uart_web_proc.h"
#include "cmsis_os.h"
#include "FreeRTOS.h"

extern uint8_t lockState;
extern UART_HandleTypeDef huart5;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;
extern osSemaphoreId uartVisualHandle;

void uart_visual_proc(void);

#endif
