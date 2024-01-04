#include "light_control.h"

uint16_t value_light;

int8_t Counter = 0;

uint8_t Flag = 0;

uint16_t adc_average = 0;

void EXTI4_judge(void)
{
	if (Flag == 0 | Flag == 1)
		Flag = 1;
	else if (Flag == 2)
	{
		Flag = 3;
		Counter++;
		Flag = 0;
	}
}

void EXTI5_judge(void)
{

	if (Flag == 0 | Flag == 2)
		Flag = 2;
	else if (Flag == 1)
	{
		Flag = 4;
		Counter--;
		Flag = 0;
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{

	if (GPIO_Pin == GPIO_PIN_4)
	{
		if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4) == SET)
			EXTI4_judge();
		while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4) == SET)
			;
	}
	if (GPIO_Pin == GPIO_PIN_5)
	{
		if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5) == SET)
			EXTI5_judge();
		while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5) == SET)
			;
	}
}

void light_control(void)
{

	if (value_light > 2000)
	{
		lightState = HIGH;
	}
	else if (value_light > 1000)
	{
		lightState = MID;
	}
	else if (value_light > 500)
	{
		lightState = LOW;
	}
}

void light_sensor(void)
{
	for (int i = 0; i < 10; i++)
	{
		adc_average += adc_value[i];
	}
	value_light = adc_average / 10;
	adc_average = 0;
}

void led_ctrl(uint8_t state)
{
	switch (state)
	{
	case DEVICE_OFF:
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_5, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_6, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_7, GPIO_PIN_SET);
		break;
	case DEVICE_ON:
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_5, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_6, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_7, GPIO_PIN_SET);
		break;
	case LOW:
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_5, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_6, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_7, GPIO_PIN_SET);
		break;
	case MID:
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_5, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_6, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_7, GPIO_PIN_SET);
		break;
	case HIGH:
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_5, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_6, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_7, GPIO_PIN_RESET);
		break;
	default:
		break;
	}
}
