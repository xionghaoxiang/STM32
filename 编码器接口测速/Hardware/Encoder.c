#include "stm32f10x.h"                  // Device header
void Encoder_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);// Enable the GPIOA clock
    GPIO_InitTypeDef GPIO_InitStructure; 
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 ;
    GPIO_InitStructure.GPIO_Mode =GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
   

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
    
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_Period = 65536-1;   //ARR
    TIM_TimeBaseInitStructure.TIM_Prescaler = 0; //PSC
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;   
    TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
   

    TIM_ICInitTypeDef  TIM_ICInitStructure;
    TIM_ICStructInit(&TIM_ICInitStructure);
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_1  ;
    TIM_ICInitStructure.TIM_ICFilter = 15;
//  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
    TIM_ICInit(TIM3,&TIM_ICInitStructure);


    
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_2  ;
    TIM_ICInitStructure.TIM_ICFilter = 15;
//  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
    TIM_ICInit(TIM3,&TIM_ICInitStructure);

    TIM_EncoderInterfaceConfig(TIM3,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);
    TIM_Cmd(TIM3,ENABLE);
}
int16_t Encoder_Get(void)
{
    int16_t tmp;
    tmp=TIM_GetCounter(TIM3);
    TIM_SetCounter(TIM3,0);
    return tmp;
}
