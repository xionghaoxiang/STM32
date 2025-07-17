#include "stm32f10x.h"                  // Device header
#ifndef __SERIAL_H
#define __SERIAL_H
#include <stdio.h>
extern uint8_t Serial_TXPacket[4];
extern char Serial_RXPacket[100];
extern uint8_t Serial_RxFlag;
void Serial_SendPacket(void);
void Serial_Init(void);
void Serial_SendByte(uint8_t Byte);
void Serial_SendArray(uint8_t *Array, uint16_t Length);
void Serial_SendString(char *String);
void Serial_SendNumber(uint32_t Number, uint8_t Length);
void Serial_Printf(char *format, ...);

uint8_t Serial_GetRxFlag(void);
uint8_t Serial_GetRxData(void);

#endif
