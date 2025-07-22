#include "stm32f10x.h"
#include "Delay.h"
void Encoder_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 |GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);

    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource9);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource8);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 |GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&GPIO_InitStructure);
    GPIO_SetBits(GPIOB,GPIO_Pin_5);
    GPIO_SetBits(GPIOB,GPIO_Pin_6);

    EXTI_InitTypeDef EXTI_InitStructure;
    EXTI_InitStructure.EXTI_Line = EXTI_Line8  ;
    EXTI_InitStructure.EXTI_LineCmd =ENABLE ;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_Init(&EXTI_InitStructure);

    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
    NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;

    NVIC_Init(&NVIC_InitStructure);
}
void Encoder_Stop(void)
{
    EXTI_InitTypeDef EXTI_InitStructure;
    EXTI_InitStructure.EXTI_Line = EXTI_Line8  ;
    EXTI_InitStructure.EXTI_LineCmd =DISABLE ;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_Init(&EXTI_InitStructure);
}
void Encoder_Continue(void)
{
    EXTI_InitTypeDef EXTI_InitStructure;
    EXTI_InitStructure.EXTI_Line = EXTI_Line8  ;
    EXTI_InitStructure.EXTI_LineCmd =ENABLE ;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_Init(&EXTI_InitStructure);
}
void  EXTI9_5_IRQHandler(void)
{

    if (EXTI_GetITStatus(EXTI_Line8) == SET)
    {
        if (GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_9)==0)
            {
            GPIO_ResetBits(GPIOB,GPIO_Pin_5);
            Delay_ms(200);
            GPIO_SetBits(GPIOB,GPIO_Pin_5);
            EXTI_ClearITPendingBit(EXTI_Line8);
            }

        else
            {
            GPIO_ResetBits(GPIOB,GPIO_Pin_6);
            Delay_ms(200);
            GPIO_SetBits(GPIOB,GPIO_Pin_6);
            EXTI_ClearITPendingBit(EXTI_Line8);
            }        

        
    }

    
}
