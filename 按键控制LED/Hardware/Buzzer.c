#include "stm32f10x.h"
void Buzzer_Init(void)//初始化PA1，PA2作为输出
{
    GPIO_InitTypeDef GPIO_InitStructure;
    // Enable the GPIOA clock
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_SetBits(GPIOB, GPIO_Pin_12); 
}
void Buzzer_On(uint16_t Buzzer)
{
    GPIO_ResetBits(GPIOB, Buzzer); 
}
void Buzzer_Off(uint8_t Buzzer)
{
    GPIO_SetBits(GPIOB, Buzzer); 
}
void Buzzer_turn(uint8_t Buzzer)
{
    if(GPIO_ReadOutputDataBit(GPIOA,Buzzer)==0)
    {
        GPIO_SetBits(GPIOB,Buzzer);
    }
    else GPIO_ResetBits(GPIOB,Buzzer);
}