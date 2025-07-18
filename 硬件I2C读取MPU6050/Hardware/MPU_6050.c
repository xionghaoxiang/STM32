#include "stm32f10x.h"

#include "MPU6050_Reg.h"
#define MPU6050_Address 0xD0
void MPU6050_WaitEvent(I2C_TypeDef* I2Cx, uint32_t I2C_EVENT)
{   uint32_t time_out = 10000;
    while( I2C_CheckEvent(I2Cx,I2C_EVENT) != SUCCESS);
    {
        time_out--;
        if (time_out == 0)
        {
            return ;
        }
    }
    
}
void MPU6050_WriteReg(uint8_t RegAddress,uint8_t Data)
{  
    I2C_GenerateSTART(I2C2,ENABLE);
    MPU6050_WaitEvent(I2C2,I2C_EVENT_MASTER_MODE_SELECT);

    
    I2C_Send7bitAddress(I2C2,MPU6050_Address,I2C_Direction_Transmitter);
    MPU6050_WaitEvent(I2C2,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) ;

    I2C_SendData(I2C2,RegAddress);
    MPU6050_WaitEvent(I2C2,I2C_EVENT_MASTER_BYTE_TRANSMITTING) ;
    
    I2C_SendData(I2C2,Data);
    MPU6050_WaitEvent(I2C2,I2C_EVENT_MASTER_BYTE_TRANSMITTED) ;

    I2C_GenerateSTOP(I2C2,ENABLE);


}
uint8_t MPU6050_ReadReg(uint8_t RegAddress)
{

    I2C_GenerateSTART(I2C2,ENABLE);
    while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS);
    
    I2C_Send7bitAddress(I2C2,MPU6050_Address,I2C_Direction_Transmitter);
    while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) != SUCCESS);

    I2C_SendData(I2C2,RegAddress);
    while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_BYTE_TRANSMITTED) != SUCCESS);

    I2C_GenerateSTART(I2C2,ENABLE);
    while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS);

    I2C_Send7bitAddress(I2C2,MPU6050_Address,I2C_Direction_Receiver);
    while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED) != SUCCESS);

    I2C_AcknowledgeConfig(I2C2,DISABLE);
    I2C_GenerateSTOP(I2C2,ENABLE);
    while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_BYTE_RECEIVED ) != SUCCESS);
    uint8_t data = I2C_ReceiveData(I2C2);

    I2C_AcknowledgeConfig(I2C2,ENABLE);

    return data;

}
void MPU6050_Init(void)
{
    // MyI2C_Init();

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&GPIO_InitStructure);
    I2C_InitTypeDef  I2C_InitStructure;
    I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_InitStructure.I2C_ClockSpeed = 50000;
    I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_16_9;
    I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
    I2C_InitStructure.I2C_OwnAddress1 = 0x00;

    I2C_Init(I2C2,&I2C_InitStructure);
    I2C_Cmd(I2C2,ENABLE);

    MPU6050_WriteReg(MPU6050_PWR_MGMT_1,0x01);
    MPU6050_WriteReg(MPU6050_PWR_MGMT_2,0x00);
    MPU6050_WriteReg(MPU6050_SMPLRT_DIV,0x09);
    MPU6050_WriteReg(MPU6050_CONFIG,0x06);
    MPU6050_WriteReg(MPU6050_GYRO_CONFIG,0x18);
    MPU6050_WriteReg(MPU6050_ACCEL_CONFIG,0x18);
}
void MPU6050_GetData(int16_t *Accx,int16_t *Accy, int16_t *Accz, int16_t *Gyrox,int16_t *Gyroy, int16_t *Gyroz)
{   uint8_t data_H,data_L;
    data_H = MPU6050_ReadReg(MPU6050_ACCEL_XOUT_H);
    data_L = MPU6050_ReadReg(MPU6050_ACCEL_XOUT_L);
    *Accx = ((data_H << 8) | data_L);
    data_H = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_H);
    data_L = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_L);
    *Accy = ((data_H << 8) | data_L);
    data_H = MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_H);
    data_L = MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_L);
    *Accz = ((data_H << 8) | data_L);
    data_H = MPU6050_ReadReg(MPU6050_GYRO_XOUT_H);
    data_L = MPU6050_ReadReg(MPU6050_GYRO_XOUT_L);
    *Gyrox = ((data_H << 8) | data_L);
    data_H = MPU6050_ReadReg(MPU6050_GYRO_YOUT_H);
    data_L = MPU6050_ReadReg(MPU6050_GYRO_YOUT_L);
    *Gyroy = ((data_H << 8) | data_L);
    data_H = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_H);
    data_L = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_L);
    *Gyroz = ((data_H << 8) | data_L);
}
uint8_t  MPU6050_GetID(void)
{
    return MPU6050_ReadReg(MPU6050_WHO_AM_I);
}
