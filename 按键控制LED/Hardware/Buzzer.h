#include "stm32f10x.h"
#ifndef __Buzzer_H
#define __Buzzer_H
void Buzzer_Init(void);
void Buzzer_On(uint8_t Buzzer);
void Buzzer_Off(uint8_t Buzzer);
void Buzzer_turn(uint8_t Buzzer);
#endif
