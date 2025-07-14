#include "stm32f10x.h"                  // Device header
#include "Delay.h"
int main()
{
		
		GPIO_InitTypeDef  GPIO_InitStructure;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		//GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2  '''''''''     ;
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA,&GPIO_InitStructure);
		int x=1;
		while(1)
		{
			
			GPIO_Write(GPIOA,x);
			Delay_ms(100);
			x=x*2;
			if(x==128)
				x=1;
		}

}

