#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "Key.h"
#include "Buzzer.h"
#include "LightSensor.h"
int main()
{

	Buzzer_Init();
	LightSensor_Init();

		while(1)
		{
			if (LightSensor_Get()==1)
			{Buzzer_Off();}
			else Buzzer_On();
		}
  
}

