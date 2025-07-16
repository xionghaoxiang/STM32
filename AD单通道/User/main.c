#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "AD.h"
float Voltage;
int main()
{
	OLED_Init();
	AD_Init();
	OLED_ShowString(1,1,"AD_Value:");
	OLED_ShowString(2,1,"Voltage:0.00v");
		while(1)
		{
			Voltage = AD_GetValue()/4095.0*3.3,4;
			OLED_ShowNum(1,9,AD_GetValue(),4);
			OLED_ShowNum(2,9,Voltage,1);
			OLED_ShowNum(2,11,(uint16_t)(Voltage*100) % 100,2);
			Delay_ms(100);

		}
  
}

