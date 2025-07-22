#include "stm32f10x.h"                  // Device header
void AD_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
    
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);


    ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_55Cycles5);

    ADC_InitTypeDef ADC_InitStructure;
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE; //连续还是单次
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right ;// ADC 数据寄存器对齐格式
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;// ADC 转换触发信号选择
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;// ADC 工作模式选择， 只使用一个ADC独立模式
    ADC_InitStructure.ADC_NbrOfChannel = 1;// ADC 采集通道数
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;// ADC 扫描（多通道）或者非扫描（单通道）模式选择 
    ADC_Init(ADC1,&ADC_InitStructure);

    ADC_Cmd(ADC1,ENABLE);
    ADC_ResetCalibration(ADC1);
    while(ADC_GetResetCalibrationStatus(ADC1)==SET);
    ADC_StartCalibration(ADC1);
    while(ADC_GetCalibrationStatus(ADC1)==SET);

}
uint16_t AD_GetValue(void)
{
    ADC_SoftwareStartConvCmd(ADC1,ENABLE);
    while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC)==RESET);
    return (ADC_GetConversionValue(ADC1));
}