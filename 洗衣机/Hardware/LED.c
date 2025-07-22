#include "stm32f10x.h"                  // Device header

void LED_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_0 |GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOA, GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_0 | GPIO_Pin_7);
}

void LED1_ON(void)
{
	GPIO_ResetBits(GPIOA, GPIO_Pin_1);
}

void LED1_OFF(void)
{
	GPIO_SetBits(GPIOA, GPIO_Pin_1);
}

void LED3_ON(void)
{
	GPIO_ResetBits(GPIOA, GPIO_Pin_0);
}

void LED3_OFF(void)
{
	GPIO_SetBits(GPIOA, GPIO_Pin_0);
}
void LED4_ON(void)
{
	GPIO_ResetBits(GPIOA, GPIO_Pin_7);
}

void LED4_OFF(void)
{
	GPIO_SetBits(GPIOA, GPIO_Pin_7);
}
uint8_t LED1_Turn(void)
{
	uint8_t n;
	if (GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_1) == 0)
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_1);
		n=1;
	}
	else
	{
		GPIO_ResetBits(GPIOA, GPIO_Pin_1);
		n=0;
	}
	return n;
}

void LED2_ON(void)
{
	GPIO_ResetBits(GPIOA, GPIO_Pin_2);
}

void LED2_OFF(void)
{
	GPIO_SetBits(GPIOA, GPIO_Pin_2);
}

void LED2_Turn(void)
{
	if (GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_2) == 0)
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_2);
	}
	else
	{
		GPIO_ResetBits(GPIOA, GPIO_Pin_2);
	}
}
