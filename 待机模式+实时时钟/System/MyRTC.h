#include "stm32f10x.h"
#ifndef __MYRTC_H
#define __MYRTC_H
void MyRTC_Init(void);
void MyRTC_Readtime(void);
void MyRTC_Settime(void);
extern uint16_t MyRTC_time[];
#endif  
