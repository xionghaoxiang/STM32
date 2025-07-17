#include "stm32f10x.h"                  // Device header
#include <stdio.h>
#ifndef __SERIAL_H
#define __SERIAL_H
void Serial_SendByte(uint8_t byte);
void Serial_Init(void);
void Serial_SendArray(uint8_t *Array,uint16_t length);
void Serial_SendString(char *String);
void Serial_SendNumber(uint32_t Number,uint8_t length);
int fputc(int ch,FILE *f);
#endif  
