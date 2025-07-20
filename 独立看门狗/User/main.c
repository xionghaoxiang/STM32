#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Key.h"
int main()
{
	OLED_Init();

	Key_Init();
	OLED_ShowString(1,1,"IWDG TEST");

	if(RCC_GetFlagStatus(RCC_FLAG_IWDGRST) == SET)
	{
		RCC_ClearFlag();
		OLED_ShowString(2,1,"IWDGRST");
		Delay_ms(500);
		OLED_ShowString(2,1,"        ");
		Delay_ms(100);
	}
	else
	{
		OLED_ShowString(3,1,"RST");
		Delay_ms(500);
		OLED_ShowString(3,1,"        ");
		Delay_ms(100);
	}

	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
	IWDG_SetPrescaler(IWDG_Prescaler_16);
	IWDG_SetReload(2499); //1000ms
	IWDG_ReloadCounter();
	IWDG_Enable();
		while(1)
		{	
			Key_Getnum();
			IWDG_ReloadCounter();
			OLED_ShowString(4,1,"Feed");
			Delay_ms(200);
			OLED_ShowString(4,1,"      ");
			Delay_ms(600);
		}
  
}

