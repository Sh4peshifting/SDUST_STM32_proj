#include "fire_detect.h"

extern bool alarm_off_flag;

//=========================
//tempΪ������¶ȴ�С state 0��ʾ������ 1��ʾ���ַ����������� 2��ʾ���������������� 3Ϊ������
//=========================
uint8_t Fire_Human_System(uint8_t temp)
{
	uint8_t state = 0;

	static uint8_t last_state_hu = 0;
	
	if(temp >= 28 && gas_Seneor_Do == 0)
	{
		state |= 0x01;
		alarm_off_flag = false;
	}
	if(human_detectrion_flag == 1)
	{
		state |= 0x02;	
		if (last_state_hu == 0)
		{
			alarm_off_flag = false;
		}
	}
	else
	{
		state &= ~0x02;
	}
	last_state_hu = human_detectrion_flag;
	return state;
}
	
	
	


