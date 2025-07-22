#include "stm32f10x.h"                  // Device header
#include "DC.h"

void Servo_Init(void)
{
	DC_Init();
}

void Servo_SetAngle(float Angle)
{
	DC_SetCompare2(Angle / 180 * 2000 + 500);
}
