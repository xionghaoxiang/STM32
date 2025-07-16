#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "PWM.h"
#include "IC.h"
int main()
{
	OLED_Init();
 
	//为了产生一个信号，如果有信号发生器可以不用信号产生
	PWM_Init();     
	PWM_SetPrescaler(72-1);//修改TIM2的预分频PSR改变频率，默认在PWM_Init中ARR的值为100-1  Freq = 72M/PSR+1/ARR+1
	PWM_SetCompare(20); //修改TIM2的与ARR比较的数值产生的信号波形的占空比

	IC_Init(); //信号测量
	OLED_ShowString(1,1,"Freq:00000HZ");
	OLED_ShowString(2,1,"Duty:00%");
		while(1)
		{
			OLED_ShowNum(1,6,IC_GetFrequce(),5);
			OLED_ShowNum(2,6,IC_GetDuty(),2);
			
		}
  
}

