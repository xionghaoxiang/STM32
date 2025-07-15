#include "stm32f10x.h"                  // Device header
void IC_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);// Enable the GPIOA clock
    GPIO_InitTypeDef GPIO_InitStructure; 
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 ;
    GPIO_InitStructure.GPIO_Mode =GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
   

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
    TIM_InternalClockConfig(TIM3);
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_Period = 65536-1;   //ARR
    TIM_TimeBaseInitStructure.TIM_Prescaler = 72-1; //PSC
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;   
    TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
   

    TIM_ICInitTypeDef  TIM_ICInitStructure;
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_1  ;
    TIM_ICInitStructure.TIM_ICFilter = 15;
    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
    TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
    
    TIM_PWMIConfig(TIM3,&TIM_ICInitStructure);//对结构体进行互补的配置，这里相当于配置通道2，下降沿，交叉
    
    TIM_ICInit(TIM3,&TIM_ICInitStructure);

    TIM_SelectInputTrigger(TIM3,TIM_TS_TI1FP1);
    TIM_SelectSlaveMode(TIM3,TIM_SlaveMode_Reset);

    TIM_Cmd(TIM3,ENABLE);
}
uint32_t IC_GetFrequce(void)
{
    return 1000000/(TIM_GetCapture1(TIM3)+1);
}
uint32_t IC_GetDuty(void)
{
    return (TIM_GetCapture2(TIM3)+1)*100/(TIM_GetCapture1(TIM3)+1);
}
