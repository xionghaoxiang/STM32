#include "stm32f10x.h"
#ifndef __MPU_6050_H
#define __MPU_6050_H
void MPU6050_WriteReg(uint8_t RegAddress,uint8_t Data);
uint8_t MPU6050_ReadReg(uint8_t RegAddress);
void MPU6050_Init(void);
void MPU6050_GetData(int16_t *,int16_t *, int16_t *, int16_t *,int16_t *, int16_t *);
uint8_t MPU6050_GetID(void);
#endif
