#include "stm32f10x.h"                  // Device header
#ifndef __CountSensor_H
#define __CountSensor_H
void CountSensor_Init(void);
uint16_t CountSensor_Get(void);
#endif
