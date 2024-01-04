#ifndef __LIGHT_CONTROL_H
#define __LIGHT_CONTROL_H

#include "stm32f1xx_hal.h"
#include "uart_web_proc.h"
#include "main.h"

extern int8_t Counter;
extern ADC_HandleTypeDef hadc1;

extern uint16_t adc_value[10];

void light_control(void);
void led_ctrl(uint8_t state);
void light_sensor(void);
void EXTI4_judge(void);
void EXTI5_judge(void);


#endif

