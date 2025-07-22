#ifndef __COUNT_SENSOR_H
#define __COUNT_SENSOR_H

#define COUNT_HOLD				0x01  
#define COUNT_DOWN				0x02  //关闭瞬间事件
#define COUNT_UP					0x04  //打开瞬间事件

void CountSensor_Init(void);
uint8_t CountSensor_Check(uint8_t Flag);
void CountSensor_Tick(void);
void CountSensor_clearAllFlags(void);

#endif
