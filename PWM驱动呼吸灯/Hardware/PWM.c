#include "stm32f10x.h"                  // Device header

void PWM_Init(void)
{  
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    // Enable the GPIOA clock
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 ;
    GPIO_InitStructure.GPIO_Mode =GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_SetBits(GPIOA, GPIO_Pin_0); // Set the pins high to turn off the LEDs


/*引脚重映射PA0输出改到PA15输出记得上面GPIO初始化的PIN也要改成PIN15

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
    GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2,ENABLE);
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);

*/


    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
    TIM_InternalClockConfig(TIM2);
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_Period = 100-1;   //ARR
    TIM_TimeBaseInitStructure.TIM_Prescaler = 720-1; //PSC
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;   
    TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
    TIM_Cmd(TIM2,ENABLE);

    TIM_OCInitTypeDef  TIM_OCInitStructure;
    TIM_OCStructInit(&TIM_OCInitStructure);
    //TIM_OCInitStructure.TIM_OCIdleState = ;
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1   ;
    //TIM_OCInitStructure.TIM_OCNIdleState = ;
    //TIM_OCInitStructure.TIM_OCNPolarity = ;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High ;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable ;
    TIM_OCInitStructure.TIM_Pulse = 50; //CCR的值
    TIM_OC1Init(TIM2,&TIM_OCInitStructure);
}

void PWM_SetCompare(uint16_t Compare)
{
    TIM_SetCompare1(TIM2,Compare);
}