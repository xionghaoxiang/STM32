#include "stm32f10x.h"
#ifndef __STORE_H
#define __STORE_H
void Store_Clear(void);
void Store_Save(void);
void Store_Init(void);
extern uint16_t Store_Data[];
#endif
