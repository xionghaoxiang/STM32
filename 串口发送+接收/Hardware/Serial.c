#include "stm32f10x.h"                  // Device header
#include <stdio.h>
uint8_t Serial_RXdata;
uint8_t Serial_RXflag;
void Serial_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 ;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 ;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);

    USART_InitTypeDef USART_InitStructure;
    USART_InitStructure.USART_BaudRate = 9600;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_Init(USART1,&USART_InitStructure);

    //  USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);

    //  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    //  NVIC_InitTypeDef NVIC_Structure;
    //  NVIC_Structure.NVIC_IRQChannel = USART1_IRQn;
    //  NVIC_Structure.NVIC_IRQChannelCmd = ENABLE;
    //  NVIC_Structure.NVIC_IRQChannelPreemptionPriority = 1;
    //  NVIC_Structure.NVIC_IRQChannelSubPriority = 1;
    //  NVIC_Init(&NVIC_Structure);
    

    USART_Cmd(USART1,ENABLE);
}

void Serial_SendByte(uint8_t byte)
{
    USART_SendData(USART1,byte);
    while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);

}
void Serial_SendArray(uint8_t *Array,uint16_t length)
{
    uint16_t i;
    for ( i = 0; i < length; i++)
    {
        Serial_SendByte(Array[i]);
    }
    
}
void Serial_SendString(char *String)
{
    uint8_t i;
    for ( i = 0; String[i] !='\0'; i++)
    {
        Serial_SendByte(String[i]);
    }
    
}
uint32_t Serial_Power(uint32_t x,uint32_t y)
{
    uint32_t Result = 1;
    while(y--)
    {
        Result *=x; 
    }
return Result;
}
void Serial_SendNumber(uint32_t Number,uint8_t length)
{
    uint8_t i;
    for (i=0;i<=length-1;i++)
    {
        Serial_SendByte(Number/Serial_Power(10,(length-i-1))%10+'0');
    }
}
int fputc(int ch,FILE *f)
{
    Serial_SendByte(ch);
    return ch;
}
uint8_t Serial_GetRXflag(void)
{
    if(Serial_RXflag == 1)
    {
        Serial_RXflag =0;
        return 1;
    }
    else return 0;
}
uint8_t Serial_GetRXdata(void)
{
    return Serial_RXdata;
}
//  void  USART1_IRQHandler(void)
//  {
//      if (USART_GetITStatus(USART1,USART_IT_RXNE)==SET)
//      {
//              Serial_RXdata = USART_ReceiveData(USART1);
//              Serial_RXflag = 1;
//              USART_ClearITPendingBit(USART1,USART_IT_RXNE);
//      }
//  }
