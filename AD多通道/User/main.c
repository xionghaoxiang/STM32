#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "AD.h"
float Voltage;
uint16_t AD0,AD1,AD2,AD3;
int main()
{
	OLED_Init();
	AD_Init();
	OLED_ShowString(1,1,"AD0:");
	OLED_ShowString(2,1,"AD1:");
	OLED_ShowString(3,1,"AD2:");
	OLED_ShowString(4,1,"AD3:");
	
		while(1)
		{
			AD0=AD_GetValue(ADC_Channel_0);
			AD1=AD_GetValue(ADC_Channel_1);
			AD2=AD_GetValue(ADC_Channel_2);
			AD3=AD_GetValue(ADC_Channel_3);
			OLED_ShowNum(1,5,AD0,5);
			OLED_ShowNum(2,5,AD1,5);
			OLED_ShowNum(3,5,AD2,5);
			OLED_ShowNum(4,5,AD3,5);



			Delay_ms(100);

		}
  
}

