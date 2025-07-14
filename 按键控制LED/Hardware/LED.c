#include "stm32f10x.h"
void LED_Init(void)//初始化PA1，PA2作为输出
{
    GPIO_InitTypeDef GPIO_InitStructure;
    // Enable the GPIOA clock
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_SetBits(GPIOA, GPIO_Pin_1 | GPIO_Pin_2); // Set the pins high to turn off the LEDs
}
void LED_On(uint8_t led)
{
    GPIO_ResetBits(GPIOA, led); // Set the pins low to turn on the LEDs
}
void LED_Off(uint8_t led)
{
    GPIO_SetBits(GPIOA, led); // Set the pins high to turn off the LEDs
}
void LED_turn(uint8_t ledport)
{
    if(GPIO_ReadOutputDataBit(GPIOA,ledport)==0)
    {
        GPIO_SetBits(GPIOA,ledport);
    }
    else GPIO_ResetBits(GPIOA,ledport);
}