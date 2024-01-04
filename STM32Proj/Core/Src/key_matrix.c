#include "key_matrix.h"

uint16_t Password = 0;
uint16_t Count = 0;

unsigned char KeyNum = 0;

/**
  * @brief  ������̶�ȡ��������
  * @param  ��
  * @retval KeyNumber ���°����ļ���ֵ
			����������²��ţ������ͣ���ڴ˺��������ֵ�һ˲�䣬���ذ������룬û�а�������ʱ������0
			��������ʵ�ֵĹ��̾��Ƕ�16�����󰴼�ɨ����һ��
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
		if (KeyNum <= 10) // ���S1~S10�������£���������
		{
			if (Count < 4) // ����������С��4
			{
				Password *= 10;			 // ��������һλ
				Password += KeyNum % 10; // ��ȡһλ����
				Count++;				 // �ƴμ�һ
			}
		}
		if (KeyNum == 11) // ���S11�������£�ȷ��
		{
			if (Password == 2345) // ������������ȷ����
			{
				lockState = UNLOCKED;	  // ִ�к���;
				HAL_UART_Transmit(&huart3, (uint8_t *)&"U", 1, 50);
				vTaskDelay(1);
				HAL_UART_Transmit(&huart2, (uint8_t *)&"Door Unlocked", 14, 50);
				Password = 0; // ��������
				Count = 0;	  // �ƴ�����
			}
			else // ����
			{
				// ��ʾERR
				HAL_UART_Transmit(&huart2, (uint8_t *)&"Password Error", 15, 50);
				Password = 0; // ��������
				Count = 0;	  // �ƴ�����
			}
		}
		if (KeyNum == 12) // ���S12�������£�ȡ��
		{
			Password = 0; // ��������
			Count = 0;	  // �ƴ�����
		}

		if (KeyNum == 13) // ���S13��������,deleteһλ
		{

			Password /= 10;

			Count--; // �ƴμ�һ
		}

		if (KeyNum == 14) // ������������ҳ��
		{
		}
	}
}
