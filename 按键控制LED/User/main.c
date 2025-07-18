#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "Key.h"
int main()
{
	int keynum;	
	LED_Init();  // Initialize the LED hardware
	Key_Init();
	
		while(1)
		{
			keynum = Key_Getnum();
			if (keynum==1)
			{
				LED_turn(GPIO_Pin_1);
			}
			if (keynum == 2)
			{
				LED_turn(GPIO_Pin_2);
			}
		}
  
}

