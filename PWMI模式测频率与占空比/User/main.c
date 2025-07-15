#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "PWM.h"
#include "IC.h"
int main()
{
	OLED_Init();

	PWM_Init();
	PWM_SetPrescaler(7200-1);
	PWM_SetCompare(80); //修改TIM2产生的信号波形

	IC_Init();
	OLED_ShowString(1,1,"Freq:00000HZ");
	OLED_ShowString(2,1,"Duty:00%");
		while(1)
		{
			OLED_ShowNum(1,6,IC_GetFrequce(),5);
			OLED_ShowNum(2,6,IC_GetDuty(),2);
			
		}
  
}

