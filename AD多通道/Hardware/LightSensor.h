#include "stm32f10x.h"                  // Device header
#ifndef __LightSensor_H
#define __LightSensor_H
void LightSensor_Init(void);
uint8_t LightSensor_Get(void);
#endif
