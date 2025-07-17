#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"
int main()
{
	// uint8_t MyArray[]={'A','B','C','D'};
	OLED_Init();
	Serial_Init();
	// Serial_SendByte('A');
	// Serial_SendArray(MyArray,4);
	// Serial_SendString("Hello,world!");
	Serial_SendNumber(12345,5);
	// printf("Num=%d\r\n",666);
		while(1)
		{
		
		}
  
}

