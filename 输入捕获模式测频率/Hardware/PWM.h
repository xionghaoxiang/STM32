#include "stm32f10x.h"                  // Device header
#ifndef __PWM_H
#define __PWM_H
void PWM_Init(void);
void PWM_SetCompare(uint16_t Compare);
void PWM_SetPrescaler(uint16_t PSC);  //修改PSC
#endif
