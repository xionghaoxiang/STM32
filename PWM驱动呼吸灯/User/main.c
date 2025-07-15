#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "PWM.h"
int main()
{
	uint8_t num;
	OLED_Init();
	PWM_Init();
		while(1)
		{
			for(num=0;num<=100;num++)
			{PWM_SetCompare(num);
			Delay_ms(10);}
			for(num=0;num<=100;num++)
			{PWM_SetCompare(100-num);
			Delay_ms(10);}
		}
  
}

