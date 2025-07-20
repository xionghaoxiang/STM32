#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Key.h"
int main()
{
	OLED_Init();

	Key_Init();
	OLED_ShowString(1,1,"WWDG TEST");

	if(RCC_GetFlagStatus(RCC_FLAG_WWDGRST) == SET)
	{
		RCC_ClearFlag();
		OLED_ShowString(2,1,"WWDGRST");
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

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG,ENABLE);
	WWDG_SetPrescaler(WWDG_Prescaler_8);
	WWDG_Enable(54 | 0x40); //50ms
	WWDG_SetWindowValue(21 | 0x40); //30ms 
		while(1)
		{	
			Key_Getnum();	
			// OLED_ShowString(4,1,"Feed");
			// Delay_ms(20);
			// OLED_ShowString(4,1,"      ");
			Delay_ms(49);
			WWDG_SetCounter(54 | 0x40);	
		}
  
}

