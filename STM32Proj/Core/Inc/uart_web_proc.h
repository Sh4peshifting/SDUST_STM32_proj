#ifndef __UART_WEB_PROC_H
#define __UART_WEB_PROC_H
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "cmsis_os.h"
#include "FreeRTOS.h"
#include "uart_audio_proc.h"

#include "main.h"

#define WEB_LOCK_CTRL 0x00
#define WEB_ALARM_CTRL 0x01
#define WEB_LIGHT_CTRL 0x02
#define WEB_FAN_CTRL 0x03
#define WEB_AUTO_CTRL 0x04

#define WEB_MODE_ON 0x01
#define WEB_MODE_OFF 0x02
#define WEB_MODE_LOW 0x03
#define WEB_MODE_MID 0x04
#define WEB_MODE_HIGH 0x05

#define LOCKED 0x01
#define UNLOCKED 0x02

#define DEVICE_ON 0x01
#define DEVICE_OFF 0x02

#define LOW 0x03
#define MID 0x04
#define HIGH 0x05

extern DMA_HandleTypeDef hdma_usart1_rx;
extern DMA_HandleTypeDef hdma_uart4_rx;
extern UART_HandleTypeDef huart4;
extern UART_HandleTypeDef huart1;
extern DMA_HandleTypeDef hdma_usart3_rx;
extern UART_HandleTypeDef huart3;

extern osSemaphoreId uartWebSemHandle;
extern osSemaphoreId uartAirSemHandle;
extern osSemaphoreId uartAudioSemHandle;

extern int8_t Counter;

extern uint8_t rx_audio[50];

void uart_web_rx_proc(void);
void uart_air_rx_proc(void);
void uart_web_tx_proc(void);

#endif
