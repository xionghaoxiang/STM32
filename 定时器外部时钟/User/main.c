#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Timer.h"

uint16_t Num;
int main()
{
	OLED_Init();
	Timer_Init();
	OLED_ShowString(1,3,"Num:");
	OLED_ShowString(2,1,"Cnt:");

	//PB1口模拟方波发生器
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	//OLED_Clear();
		while(1)
		{
			OLED_ShowNum(1,5,Num,5);
			OLED_ShowNum(2,5,Timer_GetCount(),5);
			//PB1口模拟方波发生器50HZ
			GPIO_ResetBits(GPIOB,GPIO_Pin_1);
			Delay_ms(10);
			GPIO_SetBits(GPIOB,GPIO_Pin_1);
			Delay_ms(10);
		} 
  
}

void TIM2_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET)
    {
		Num++;
        TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
    }

}
