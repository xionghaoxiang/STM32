#include "stm32f10x.h"
#ifndef  __MYSPI_H
#define  __MYSPI_H
void MySPI_Stop(void);
void MySPI_Start(void);
void MySPI_Init(void);
uint8_t MySPI_SwapByte(uint8_t ByteSend);
#endif
