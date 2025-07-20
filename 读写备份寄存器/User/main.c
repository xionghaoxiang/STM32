#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Key.h"
int main()
{	
	uint16_t Array_Write[] = {0x1234,0x5678};
	uint16_t Array_Read[2];
	uint8_t Key_Num;
	Key_Init();
	OLED_Init();
	OLED_ShowString(1,1,"W:");
	OLED_ShowString(2,1,"R:");

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR,ENABLE);
	PWR_BackupAccessCmd(ENABLE);
	// BKP_WriteBackupRegister(BKP_DR1,0x1234);
	//OLED_ShowHexNum(1,1, BKP_ReadBackupRegister(BKP_DR1),4);

		while(1)
		{
			Key_Num =Key_Getnum();
			if(Key_Num == 1)
			{
				BKP_WriteBackupRegister(BKP_DR1,Array_Write[0]);
				BKP_WriteBackupRegister(BKP_DR2,Array_Write[1]);				
				Array_Write[0]++;
				Array_Write[1]++;

				OLED_ShowHexNum(1,3,Array_Write[0],4);
				OLED_ShowHexNum(1,8,Array_Write[1],4);
			}
			Array_Read[0] = BKP_ReadBackupRegister(BKP_DR1);
			Array_Read[1] = BKP_ReadBackupRegister(BKP_DR2);
			OLED_ShowHexNum(2,3,Array_Read[0],4);
			OLED_ShowHexNum(2,8,Array_Read[1],4);			
		}
  
}

