#ifndef __LED_H
#define __LED_H
void LED_Init(void);//初始化PA1，PA2作为输出
void LED_On(uint8_t led);//led端口控制输出0，点亮
void LED_Off(uint8_t led);//led端口控制输出1，熄灭
void LED_turn(uint8_t ledport); //led端口控制反转
#endif
