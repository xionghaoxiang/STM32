#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "PWM.h"
#include "Servo.h"
#include "Key.h"
uint8_t Key_num;
float angle;
int main()
{
	
	OLED_Init();
	Key_Init();
	Servo_Init();
	ServoSetAngle(90);
		while(1)
		{
			Key_num=Key_Getnum();
			if (Key_num==1)
			{	angle+=30;
				if (angle>=180)
					angle=0;
			}
			if (Key_num==2)
			{	angle+=60;
				if (angle>=180)
					angle=0;
			}
			ServoSetAngle(angle);
			OLED_ShowString(1,1,"Angle:");
			OLED_ShowNum(1,7,angle,3);
			
		}
  
}

