#include "motor.h"
#include "tim.h"
void Motor_Init()
{
	HAL_GPIO_WritePin(GPIOG,GPIO_PIN_10,GPIO_PIN_SET);
}

void Motor_Deinit()
{
	HAL_GPIO_WritePin(GPIOG,GPIO_PIN_10,GPIO_PIN_RESET);
}

void Open_fan(uint8_t speed)
{
	Motor_Init();
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_2);
	HAL_GPIO_WritePin(GPIOG,GPIO_PIN_11,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOG,GPIO_PIN_12,GPIO_PIN_RESET);
	switch(speed)
	{
		case 3:__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_2,LOW_M);		break;
		case 4:__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_2,MID_M);		break;
		case 5:__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_2,HIGH_M);		break;
		default:__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_2,LOW_M);		break;
	}
}

void Close_fan()
{
	Motor_Deinit();
	HAL_GPIO_WritePin(GPIOG,GPIO_PIN_11,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOG,GPIO_PIN_12,GPIO_PIN_RESET);
}


void Door_Lock_system(uint8_t state)
{
	switch(state)
	{
		case 1:__HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_1,150); break;
		case 2:__HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_1,50);	break;
	}
}



