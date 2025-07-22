#include "stm32f10x.h"                  // Device header
#include "CountSensor.h"

#define COUNT_PRESSED				1
#define COUNT_UNPRESSED     0

uint8_t COUNT_Flag;
void CountSensor_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
}
uint8_t CountSensor_Check(uint8_t Flag)
{
	if (COUNT_Flag & Flag)
	{
		if (Flag != COUNT_HOLD)
		{
			COUNT_Flag &= ~Flag;
		}
		return 1;
	}
	return 0;
}

void CountSensor_clearAllFlags(void)
{
	COUNT_Flag&=COUNT_HOLD;
}

uint8_t CountSensor_GetState(void)
{
	if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14))
	{
		return COUNT_PRESSED;
	}
	else 
	{
		COUNT_UNPRESSED;
	}
}
void CountSensor_Tick(void)
{
	static uint8_t Count;
	static uint8_t CurrState, PrevState;
	Count++;
	if(Count==20)
	{
		Count=0;
		PrevState = CurrState;
		CurrState = CountSensor_GetState();
		if(CurrState==COUNT_PRESSED)
		{
			COUNT_Flag |= COUNT_HOLD;
		}
		else
		{
			COUNT_Flag &= ~COUNT_HOLD;
		}
		if(PrevState==COUNT_UNPRESSED&&CurrState==COUNT_PRESSED)
		{
		  COUNT_Flag |= COUNT_DOWN;
		}
		else if(PrevState==COUNT_PRESSED&&CurrState==COUNT_UNPRESSED)
		{
			COUNT_Flag |= COUNT_UP;
		}
	}
}