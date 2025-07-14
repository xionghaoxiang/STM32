#include "stm32f10x.h"
#ifndef __Key_H
#define __Key_H

void Key_Init(void);//初始化PB1，PB11作为输入端口
uint8_t Key_Getnum(void);//从PB11和PB1判断那个按键输入


#endif
