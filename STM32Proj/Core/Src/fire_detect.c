#include "fire_detect.h"

extern bool alarm_off_flag;

//=========================
//temp为输入的温度大小 state 0表示都正常 1表示火灾发生防盗正常 2表示防盗工作防火正常 3为都发生
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
	
	
	


