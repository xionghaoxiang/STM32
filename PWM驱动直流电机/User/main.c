#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Motor.h"
#include "Servo.h"
#include "Key.h"
uint8_t Key_num;
int8_t Speed=0;
int main()
{
	
	OLED_Init();
	Motor_Init();
	Key_Init();
	OLED_ShowString(1,1,"Speed:");
		while(1)
		{	Key_num=Key_Getnum();
			if (Key_num==1)
			{
				Speed+=20;
				if(Speed>100)
				{
					Delay_ms(500);
					Speed=-100;
				}
			}	
			if (Key_num==2)
			{
				Speed=0;
			}
			OLED_ShowSignedNum(1,7,Speed,3);
			Motor_SetSpeed(Speed);		
		}
  
}

