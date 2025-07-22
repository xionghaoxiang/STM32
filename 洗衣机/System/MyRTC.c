#include "stm32f10x.h"                  // Device header
#include <time.h>

uint16_t MyRTC_Time[] = {2023, 1, 1, 23, 59, 55};


void MyRTC_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP, ENABLE);
	
	PWR_BackupAccessCmd(ENABLE);
	
	if (BKP_ReadBackupRegister(BKP_DR1) != 0xA5A5)
	{
		RCC_LSEConfig(RCC_LSE_ON);
		while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) != SET);
		
		RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
		RCC_RTCCLKCmd(ENABLE);
		
		RTC_WaitForSynchro();
		RTC_WaitForLastTask();
		
		RTC_SetPrescaler(32768 - 1);
		RTC_WaitForLastTask();
		
		time_t time_cnt;
	  struct tm time_date;
	
		time_date.tm_year = MyRTC_Time[0] - 1900;
		time_date.tm_mon = MyRTC_Time[1] - 1;
		time_date.tm_mday = MyRTC_Time[2];
		time_date.tm_hour = MyRTC_Time[3];
		time_date.tm_min = MyRTC_Time[4];
		time_date.tm_sec = MyRTC_Time[5];
		
		time_cnt = mktime(&time_date) - 8 * 60 * 60;
		
		RTC_SetCounter(time_cnt);
		RTC_WaitForLastTask();
		
		BKP_WriteBackupRegister(BKP_DR1, 0xA5A5);
	}
	else
	{
		RTC_WaitForSynchro();
		RTC_WaitForLastTask();
	}
	EXTI_InitTypeDef EXTI_InitStruct;
	EXTI_InitStruct.EXTI_Line = EXTI_Line17;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_Init(&EXTI_InitStruct);
	RTC_ITConfig(RTC_IT_ALR,ENABLE);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = RTCAlarm_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStruct);
	
}


void MyRTC_SetTime(uint32_t time)
{
	time_t time_cnt;
	time_t time_date;
	
	while(RTC_GetFlagStatus(RTC_FLAG_RTOFF)==RESET);
	RTC_EnterConfigMode();
	time_cnt = RTC_GetCounter();
	time_date = time_cnt+time;
	RTC_SetAlarm(time_date);
	RTC_ExitConfigMode();
	
	while(RTC_GetFlagStatus(RTC_FLAG_RTOFF)==RESET);
	RTC_ClearFlag(RTC_FLAG_ALR);
	RTC_ClearITPendingBit(RTC_IT_ALR);
	EXTI_ClearITPendingBit(EXTI_Line17);
}
