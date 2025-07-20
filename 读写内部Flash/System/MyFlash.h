#include "stm32f10x.h"
#ifndef __MYFLASH_H
#define __MYFLASH_H
uint8_t Myflash_ReadByte(uint32_t Address);
uint16_t Myflash_ReadHalfWord(uint32_t Address);
uint32_t Myflash_ReadWord(uint32_t Address);
void MyFlash_ErasePage(uint32_t PageAddress);
void MyFlash_EraseAllPages(void);
void MyFlash_ProgramHalfWord(uint32_t Address,uint16_t Data);
void MyFlash_ProgramWord(uint32_t Address,uint32_t Data);
#endif
