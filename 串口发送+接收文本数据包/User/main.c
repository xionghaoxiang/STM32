#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"
#include "LED.h"
#include <string.h>
uint8_t RxData;

int main(void)
{
	LED_Init();
	OLED_Init();
	Serial_Init();
	OLED_ShowString(1,1,"TXPacket");
	OLED_ShowString(3,1,"RXPacket");


	while (1)
	{
		 if (Serial_RxFlag == 1)
		 {
		 	OLED_ShowString(4,1,"                  ");
		 	OLED_ShowString(4,1,Serial_RXPacket);
			if(strcmp(Serial_RXPacket,"LED_ON") ==0)
			{
				LED1_ON();
				Serial_SendString("LED_ON OK\r\n");
				OLED_ShowString(2,1,"               ");
				OLED_ShowString(2,1,"LED_ON OK");
			}
			else if(strcmp(Serial_RXPacket,"LED_OFF") ==0)
			{
				LED1_OFF();
				Serial_SendString("LED_ON OK\r\n");
				OLED_ShowString(2,1,"               ");
				OLED_ShowString(2,1,"LED_OFF OK");
			}
			else 
			{
				OLED_ShowString(2,1,"ERROR");
				Serial_SendString("ERROR\r\n");
			}
			Serial_RxFlag = 0 ;

		 }
	}
}
