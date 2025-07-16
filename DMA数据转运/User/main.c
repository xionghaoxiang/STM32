#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "MYDMA.h"
uint8_t DataA[]={0x1,0x2,0x3,0x4};
uint8_t DataB[]={0x0, 0x0,0x0,0x0};

int main()
{
	OLED_Init();
	OLED_ShowString(1,1,"DataA");
	OLED_ShowString(3,1,"DataB");
	OLED_ShowHexNum(1,8,(uint32_t)DataA,8);
	OLED_ShowHexNum(3,8,(uint32_t)DataB,8);
	
	MyDMA_Init((uint32_t)&DataA[0],(uint32_t)&DataB[0],4);

	OLED_ShowHexNum(2,1,DataA[0],2);
	OLED_ShowHexNum(2,4,DataA[1],2);
	OLED_ShowHexNum(2,7,DataA[2],2);
	OLED_ShowHexNum(2,10,DataA[3],2);
	OLED_ShowHexNum(4,1,DataB[0],2);
	OLED_ShowHexNum(4,4,DataB[1],2);
	OLED_ShowHexNum(4,7,DataB[2],2);
	OLED_ShowHexNum(4,10,DataB[3],2);

	

		while(1)
		{
			for(int i=1;i<=4;i++)
			{
				DataA[i-1]++;
			}
				OLED_ShowHexNum(2,1,DataA[0],2);
				OLED_ShowHexNum(2,4,DataA[1],2);
				OLED_ShowHexNum(2,7,DataA[2],2);
				OLED_ShowHexNum(2,10,DataA[3],2);
				OLED_ShowHexNum(4,1,DataB[0],2);
				OLED_ShowHexNum(4,4,DataB[1],2);
				OLED_ShowHexNum(4,7,DataB[2],2);
				OLED_ShowHexNum(4,10,DataB[3],2);

				Delay_ms(1000);
				MyDMA_Transfer();
				OLED_ShowHexNum(2,1,DataA[0],2);
				OLED_ShowHexNum(2,4,DataA[1],2);
				OLED_ShowHexNum(2,7,DataA[2],2);
				OLED_ShowHexNum(2,10,DataA[3],2);
				OLED_ShowHexNum(4,1,DataB[0],2);
				OLED_ShowHexNum(4,4,DataB[1],2);
				OLED_ShowHexNum(4,7,DataB[2],2);
				OLED_ShowHexNum(4,10,DataB[3],2);
				Delay_ms(1000);
		}
  
}

