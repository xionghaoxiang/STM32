#include "stm32f10x.h"
#include "MyI2c.h"
#include "MPU6050_Reg.h"
#define MPU6050_Address 0xD0

void MPU6050_WriteReg(uint8_t RegAddress,uint8_t Data)
{
    MyI2C_Start();
    MyI2C_Sendbyte(MPU6050_Address);
    My_I2C_ReceiveACK();
    MyI2C_Sendbyte(RegAddress);
    My_I2C_ReceiveACK();
    MyI2C_Sendbyte(Data);
    My_I2C_ReceiveACK();
    MyI2C_Stop();
}
uint8_t MPU6050_ReadReg(uint8_t RegAddress)
{
    uint8_t data;
    MyI2C_Start();
    MyI2C_Sendbyte(MPU6050_Address);
    My_I2C_ReceiveACK();
    MyI2C_Sendbyte(RegAddress);
    My_I2C_ReceiveACK(); 
    
    MyI2C_Start();
    MyI2C_Sendbyte(MPU6050_Address | 0x01);
    My_I2C_ReceiveACK();
    data = My_I2C_ReceiveByte();
    MyI2C_SendACK(1);
    MyI2C_Stop();
    return data;

}
void MPU6050_Init(void)
{
    MyI2C_Init();
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
