#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"
uint8_t RXdata;
uint8_t RXflag;
int main()
{
	// uint8_t MyArray[]={'A','B','C','D'};
	OLED_Init();
	OLED_ShowString(1,1,"RXData:");
	Serial_Init();

		while(1)
		{
			if(USART_GetFlagStatus(USART1,USART_FLAG_RXNE)==SET)
			{
				RXdata = USART_ReceiveData(USART1);
				OLED_ShowHexNum(1,8,RXdata,2);
				Serial_SendByte(RXdata);
			}
			OLED_ShowString(2,1,"Running");
			Delay_ms(100);
			OLED_ShowString(2,1,"        ");
			Delay_ms(100);
			__WFI();

		}
  
}

