#include "key_matrix.h"

uint16_t Password = 0;
uint16_t Count = 0;

unsigned char KeyNum = 0;

/**
  * @brief  矩阵键盘读取按键键码
  * @param  无
  * @retval KeyNumber 按下按键的键码值
			如果按键按下不放，程序会停留在此函数，松手的一瞬间，返回按键键码，没有按键按下时，返回0
			整个函数实现的过程就是对16个矩阵按键扫描了一遍
  */
unsigned char MatrixKey()
{
	unsigned char KeyNumber = 0;

	C4_ON;
	C1_OFF;
	C2_OFF;
	C3_OFF;
	if (R4_Read == 1)
	{
		vTaskDelay(20);
		while (R4_Read == 1)
			;
		vTaskDelay(20);
		KeyNumber = 1;
	}
	if (R3_Read == 1)
	{
		vTaskDelay(20);
		while (R3_Read == 1)
			;
		vTaskDelay(20);
		KeyNumber = 5;
	}
	if (R2_Read == 1)
	{
		vTaskDelay(20);
		while (R2_Read == 1)
			;
		vTaskDelay(20);
		KeyNumber = 9;
	}
	if (R1_Read == 1)
	{
		vTaskDelay(20);
		while (R1_Read == 1)
			;
		vTaskDelay(20);
		KeyNumber = 13;
	}

	C3_ON;
	C1_OFF;
	C2_OFF;
	C4_OFF;
	if (R4_Read == 1)
	{
		vTaskDelay(20);
		while (R4_Read == 1)
			;
		vTaskDelay(20);
		KeyNumber = 2;
	}
	if (R3_Read == 1)
	{
		vTaskDelay(20);
		while (R3_Read == 1)
			;
		vTaskDelay(20);
		KeyNumber = 6;
	}
	if (R2_Read == 1)
	{
		vTaskDelay(20);
		while (R2_Read == 1)
			;
		vTaskDelay(20);
		KeyNumber = 10;
	}
	if (R1_Read == 1)
	{
		vTaskDelay(20);
		while (R1_Read == 1)
			;
		vTaskDelay(20);
		KeyNumber = 14;
	}

	C2_ON;
	C1_OFF;
	C3_OFF;
	C4_OFF;
	if (R4_Read == 1)
	{
		vTaskDelay(20);
		while (R4_Read == 1)
			;
		vTaskDelay(20);
		KeyNumber = 3;
	}
	if (R3_Read == 1)
	{
		vTaskDelay(20);
		while (R3_Read == 1)
			;
		vTaskDelay(20);
		KeyNumber = 7;
	}
	if (R2_Read == 1)
	{
		vTaskDelay(20);
		while (R2_Read == 1)
			;
		vTaskDelay(20);
		KeyNumber = 11;
	}
	if (R1_Read == 1)
	{
		vTaskDelay(20);
		while (R1_Read == 1)
			;
		vTaskDelay(20);
		KeyNumber = 15;
	}

	C1_ON;
	C2_OFF;
	C3_OFF;
	C4_OFF;
	if (R4_Read == 1)
	{
		vTaskDelay(20);
		while (R4_Read == 1)
			;
		vTaskDelay(20);
		KeyNumber = 4;
	}
	if (R3_Read == 1)
	{
		vTaskDelay(20);
		while (R3_Read == 1)
			;
		vTaskDelay(20);
		KeyNumber = 8;
	}
	if (R2_Read == 1)
	{
		vTaskDelay(20);
		while (R2_Read == 1)
			;
		vTaskDelay(20);
		KeyNumber = 12;
	}
	if (R1_Read == 1)
	{
		vTaskDelay(20);
		while (R1_Read == 1)
			;
		vTaskDelay(20);
		KeyNumber = 16;
	}

	return KeyNumber;
}

void password_check(void)
{
	if (KeyNum)
	{
		if (KeyNum <= 10) // 如果S1~S10按键按下，输入密码
		{
			if (Count < 4) // 如果输入次数小于4
			{
				Password *= 10;			 // 密码左移一位
				Password += KeyNum % 10; // 获取一位密码
				Count++;				 // 计次加一
			}
		}
		if (KeyNum == 11) // 如果S11按键按下，确认
		{
			if (Password == 2345) // 如果密码等于正确密码
			{
				lockState = UNLOCKED;	  // 执行函数;
				HAL_UART_Transmit(&huart3, (uint8_t *)&"U", 1, 50);
				vTaskDelay(1);
				HAL_UART_Transmit(&huart2, (uint8_t *)&"Door Unlocked", 14, 50);
				Password = 0; // 密码清零
				Count = 0;	  // 计次清零
			}
			else // 否则
			{
				// 显示ERR
				HAL_UART_Transmit(&huart2, (uint8_t *)&"Password Error", 15, 50);
				Password = 0; // 密码清零
				Count = 0;	  // 计次清零
			}
		}
		if (KeyNum == 12) // 如果S12按键按下，取消
		{
			Password = 0; // 密码清零
			Count = 0;	  // 计次清零
		}

		if (KeyNum == 13) // 如果S13按键按下,delete一位
		{

			Password /= 10;

			Count--; // 计次减一
		}

		if (KeyNum == 14) // 进入密码设置页面
		{
		}
	}
}
