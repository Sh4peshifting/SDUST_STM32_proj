#ifndef __UART_AUDIO_PROC_H__
#define __UART_AUDIO_PROC_H__

#include "uart_web_proc.h"
#include "main.h"

extern uint8_t lockState;
extern uint8_t alarmState;
extern bool alarm_off_flag;

extern uint8_t lightState;
extern uint8_t fanState;
extern uint8_t autoState;

extern DMA_HandleTypeDef hdma_usart3_rx;
extern UART_HandleTypeDef huart3;

#define AUDIO_LOCK_CTRL 0x00
#define AUDIO_ALARM_CTRL 0x01
#define AUDIO_LIGHT_CTRL 0x02
#define AUDIO_FAN_CTRL 0x03

#define AUDIO_MODE_ON 0x01
#define AUDIO_MODE_OFF 0x02
#define AUDIO_MODE_LOW 0x03
#define AUDIO_MODE_MID 0x04
#define AUDIO_MODE_HIGH 0x05

void uart_audio_proc(void);

#endif
