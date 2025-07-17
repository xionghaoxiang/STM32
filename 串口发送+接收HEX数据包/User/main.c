#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"
#include "Key.h"
uint8_t KeyNum;
uint8_t RxData;

int main(void)
{
	OLED_Init();
	Key_Init();
	Serial_Init();
	OLED_ShowString(1,1,"TXPacket");
	OLED_ShowString(3,1,"RXPacket");
	Serial_TXPacket[0]=0x01;
	Serial_TXPacket[1]=0x02;
	Serial_TXPacket[2]=0x03;
	Serial_TXPacket[3]=0x04;

	while (1)
	{
		KeyNum =Key_GetNum();
		if (KeyNum ==1)
		{
		Serial_TXPacket[0]++;
		Serial_TXPacket[1]++;
		Serial_TXPacket[2]++;
		Serial_TXPacket[3]++;			
		Serial_SendPacket();
		OLED_ShowHexNum(2,1,Serial_TXPacket[0],2);
		OLED_ShowHexNum(2,4,Serial_TXPacket[1],2);
		OLED_ShowHexNum(2,7,Serial_TXPacket[2],2);
		OLED_ShowHexNum(2,10,Serial_TXPacket[3],2);
		}
		if (Serial_GetRxFlag() == 1)
		{
			OLED_ShowHexNum(4,1,Serial_RXPacket[0],2);
			OLED_ShowHexNum(4,4,Serial_RXPacket[1],2);
			OLED_ShowHexNum(4,7,Serial_RXPacket[2],2);
			OLED_ShowHexNum(4,10,Serial_RXPacket[3],2);
		}
	}
}
