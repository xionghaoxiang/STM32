#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "MyRTC.h"
int main()
{
	OLED_Init();
	MyRTC_Init();
	OLED_ShowString(1,1,"Data:XXXX-xx-xx");
	OLED_ShowString(2,1,"TIME:XX:XX:XX");
	OLED_ShowString(3,1,"CNT:");
	OLED_ShowString(4,1,"DIV:");
		while(1)
		{
			MyRTC_Readtime();
			OLED_ShowNum(1,6,MyRTC_time[0],4);
			OLED_ShowNum(1,11,MyRTC_time[1],2);
			OLED_ShowNum(1,14,MyRTC_time[2],2);
			OLED_ShowNum(2,6,MyRTC_time[3],2);
			OLED_ShowNum(2,9,MyRTC_time[4],2);
			OLED_ShowNum(2,12,MyRTC_time[5],2);
			OLED_ShowNum(3,6,RTC_GetCounter(),10);
			OLED_ShowNum(4,6,(32767-RTC_GetDivider())/32767.0*999,10);
		}
  
}

