#include "stm32f10x.h"                  // Device header
#ifndef __IC_H
#define __IC_H
void IC_Init(void);
uint32_t IC_GetFrequce(void);
uint32_t IC_GetDuty(void);
#endif
