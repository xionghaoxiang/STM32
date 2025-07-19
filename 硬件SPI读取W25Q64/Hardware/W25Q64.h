#include "stm32f10x.h"
#ifndef __W25Q64_H
#define __W25Q64_H
void W25Q64_Init(void);
void W25Q64_ReadData(uint32_t Address, uint8_t  *dataArray, uint32_t count);
void W25Q64_PageProgram(uint32_t Address , uint8_t  *dataArray, uint16_t count);
void W25Q64_SectorErase(uint32_t Address);
void W25Q64_ReadID(uint8_t *MID ,uint16_t *DID);
#endif  
