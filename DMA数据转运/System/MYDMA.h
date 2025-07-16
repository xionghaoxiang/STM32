#include "stm32f10x.h"                  // Device header
#ifndef __MYDMA_H
#define __MYDMA_H
void MyDMA_Init(uint32_t SourceAdd,uint32_t DestAdd,uint16_t size);
void MyDMA_Transfer(void);
#endif
