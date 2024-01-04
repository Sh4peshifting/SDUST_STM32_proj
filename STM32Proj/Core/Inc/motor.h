#ifndef __MOTTOR_H
#define __MOTTOR_H

#include "stm32f1xx_hal.h"

#define LOW_M 5
#define MID_M 13
#define HIGH_M 20

void Open_fan(uint8_t );
void Close_fan(void);

void Door_Lock_system(uint8_t );


#endif
