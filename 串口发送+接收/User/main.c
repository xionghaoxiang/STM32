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
	// Serial_SendByte('A');
	// Serial_SendArray(MyArray,4);
	// Serial_SendString("Hello,world!");
	//Serial_SendNumber(12345,5);
	// printf("Num=%d\r\n",666);
		while(1)
		{
			if(USART_GetFlagStatus(USART1,USART_FLAG_RXNE)==SET)
			{
				RXdata = USART_ReceiveData(USART1);
				OLED_ShowHexNum(1,8,RXdata,2);
				Serial_SendByte(RXdata);
			}
		}
  
}

