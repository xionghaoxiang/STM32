#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Apt.h"
#include "LED.h"
#include "Key.h"
#include "stdio.h"
#include "string.h"
#include "Motor.h"
#include "Servo.h"
#include "Timer.h"
#include "CountSensor.h"
#include "MyRTC.h"
#include "Buzzer.h"
#include "Encoder.h"
#define SECONDS 6
struct FSM
{
	uint8_t IN;
	uint8_t Wsh;
	uint8_t Dyd;
	uint8_t Spin;
	uint8_t Dry;
	uint8_t WM_flag; //0正在菜单中 1正在预约模式中 2，3，4，5，6，7分别对应进水，洗涤，脱水，甩干，烘干，完成；
	uint8_t WM_Mod; //0:自定义模式，1快速模式，2标准模式，3轻柔模式，4强力模，5烘干模式
	uint8_t make;  //1;预约时间到开启洗衣机 0 没到
};

struct FSM WM_FSM;

char Apt_MENU[][50] = {"模式-> 自定义 ","进水-> %d分钟","洗涤-> %d分钟","脱水-> %d分钟","甩干-> %d分钟","烘干-> %d分钟","启动>>         "};
char Apt_make[][50] = {"时->   ","分->   ","秒->   ","确认          ","取消           "};

void MENU(void);
void run(void);
void appointment(void);

int main(void)
{
  Key_Init();
	OLED_Init();
	Timer_Init();
	LED_Init();
	MyRTC_Init();
	CountSensor_Init();
	Buzzer_Init();
	Encoder_Init();
	
	while (1)
	{
		MENU();
	}
}

void MENU(void)
{
	OLED_Clear();
	uint8_t n;
	WM_FSM.IN = 10;
	WM_FSM.Wsh = 10;
	WM_FSM.Dyd = 2;
	WM_FSM.Spin = 2;
	WM_FSM.Dry = 5 ;
	WM_FSM.WM_flag = 0;
	WM_FSM.WM_Mod = 0;
	strcpy(Apt_MENU[0],"模式-> 自定义 ");
	strcpy(Apt_MENU[1],"进水-> 10分钟 ");
	strcpy(Apt_MENU[2],"洗涤-> 10分钟 ");
	strcpy(Apt_MENU[3],"脱水-> 2分钟 ");
	strcpy(Apt_MENU[4],"甩干-> 2分钟 ");
	strcpy(Apt_MENU[5],"烘干-> 5分钟  ");

	while(1)
	{
		n = Apt_CFM(Apt_MENU,7);
		
		if(n==7||WM_FSM.make==1)
		{
			if(WM_FSM.make==1)
			{
				LED3_OFF();
				WM_FSM.make=0;
			}
			if(CountSensor_Check(COUNT_HOLD))
			{
				CountSensor_clearAllFlags();
				Key_clearAllFlags();
				run();
			}
			else
			{
				for(uint8_t i=0;i<10;i++)
				{
					LED2_Turn();
					Delay_ms(200);
				}
			}
		}
		else if(Key_Check(KEY_3,KEY_DOUBLE))
		{
			Key_clearAllFlags();
			CountSensor_clearAllFlags();
		  Apt_Dish(1);
			appointment();
		}
		else if(n==1)
		{
			WM_FSM.WM_Mod++;
			if(WM_FSM.WM_Mod==6)
			{
				WM_FSM.WM_Mod=0;
			}
			if(WM_FSM.WM_Mod==0)
			{
				WM_FSM.IN = 10;
				WM_FSM.Wsh = 10;
				WM_FSM.Dyd = 2;
				WM_FSM.Spin = 2;
				WM_FSM.Dry = 5 ;
			  sprintf(Apt_MENU[0],"模式-> 自定义 ");
				sprintf(Apt_MENU[1],"进水-> %d分钟  ",WM_FSM.IN);
				sprintf(Apt_MENU[2],"洗涤-> %d分钟  ",WM_FSM.Wsh);
				sprintf(Apt_MENU[3],"脱水-> %d分钟  ",WM_FSM.Dyd);
				sprintf(Apt_MENU[4],"甩干-> %d分钟  ",WM_FSM.Spin);
				sprintf(Apt_MENU[5],"烘干-> %d分钟  ",WM_FSM.Dry);
			}
			else if(WM_FSM.WM_Mod==1)
			{
				WM_FSM.IN = 7;
				WM_FSM.Wsh = 8;
				WM_FSM.Dyd = 1;
				WM_FSM.Spin = 1;
				WM_FSM.Dry = 0 ;
			  sprintf(Apt_MENU[0],"模式-> 快速  ");
				sprintf(Apt_MENU[1],"进水-> %d分钟  ",WM_FSM.IN);
				sprintf(Apt_MENU[2],"洗涤-> %d分钟  ",WM_FSM.Wsh);
				sprintf(Apt_MENU[3],"脱水-> %d分钟  ",WM_FSM.Dyd);
				sprintf(Apt_MENU[4],"甩干-> %d分钟  ",WM_FSM.Spin);
				sprintf(Apt_MENU[5],"烘干-> 关闭    ");
				
			}
			else if(WM_FSM.WM_Mod==2)
			{
				WM_FSM.IN = 10;
				WM_FSM.Wsh = 10;
				WM_FSM.Dyd = 2;
				WM_FSM.Spin = 2;
				WM_FSM.Dry = 5 ;
			  sprintf(Apt_MENU[0],"模式-> 标准  ");
				sprintf(Apt_MENU[1],"进水-> %d分钟  ",WM_FSM.IN);
				sprintf(Apt_MENU[2],"洗涤-> %d分钟  ",WM_FSM.Wsh);
				sprintf(Apt_MENU[3],"脱水-> %d分钟  ",WM_FSM.Dyd);
				sprintf(Apt_MENU[4],"甩干-> %d分钟  ",WM_FSM.Spin);
				sprintf(Apt_MENU[5],"烘干-> %d分钟  ",WM_FSM.Dry);
			}
			else if(WM_FSM.WM_Mod==3)
			{
				WM_FSM.IN = 8;
				WM_FSM.Wsh = 8;
				WM_FSM.Dyd = 2;
				WM_FSM.Spin = 2;
				WM_FSM.Dry = 5 ;
			  sprintf(Apt_MENU[0],"模式-> 轻柔  ");
				sprintf(Apt_MENU[1],"进水-> %d分钟  ",WM_FSM.IN);
				sprintf(Apt_MENU[2],"洗涤-> %d分钟  ",WM_FSM.Wsh);
				sprintf(Apt_MENU[3],"脱水-> %d分钟  ",WM_FSM.Dyd);
				sprintf(Apt_MENU[4],"甩干-> %d分钟  ",WM_FSM.Spin);
				sprintf(Apt_MENU[5],"烘干-> %d分钟  ",WM_FSM.Dry);
			}
			else if(WM_FSM.WM_Mod==4)
			{
				WM_FSM.IN = 15;
				WM_FSM.Wsh = 15;
				WM_FSM.Dyd = 3;
				WM_FSM.Spin = 3;
				WM_FSM.Dry = 5 ;
			  sprintf(Apt_MENU[0],"模式-> 强力  ");
				sprintf(Apt_MENU[1],"进水-> %d分钟  ",WM_FSM.IN);
				sprintf(Apt_MENU[2],"洗涤-> %d分钟  ",WM_FSM.Wsh);
				sprintf(Apt_MENU[3],"脱水-> %d分钟  ",WM_FSM.Dyd);
				sprintf(Apt_MENU[4],"甩干-> %d分钟  ",WM_FSM.Spin);
				sprintf(Apt_MENU[5],"烘干-> %d分钟  ",WM_FSM.Dry);
			}
			else if(WM_FSM.WM_Mod==5)
			{
				WM_FSM.IN = 10;
				WM_FSM.Wsh = 10;
				WM_FSM.Dyd = 3;
				WM_FSM.Spin = 3;
				WM_FSM.Dry = 15 ;
			  sprintf(Apt_MENU[0],"模式-> 烘干  ");
				sprintf(Apt_MENU[1],"进水-> %d分钟  ",WM_FSM.IN);
				sprintf(Apt_MENU[2],"洗涤-> %d分钟  ",WM_FSM.Wsh);
				sprintf(Apt_MENU[3],"脱水-> %d分钟  ",WM_FSM.Dyd);
				sprintf(Apt_MENU[4],"甩干-> %d分钟  ",WM_FSM.Spin);
				sprintf(Apt_MENU[5],"烘干-> %d分钟  ",WM_FSM.Dry);
			}
		}
		else if(n==2)
		{
			if(WM_FSM.WM_Mod==0)
			WM_FSM.IN++;
	  	sprintf(Apt_MENU[1],"进水-> %d分钟  ",WM_FSM.IN);
			if(WM_FSM.IN==16)
			{
				sprintf(Apt_MENU[1],"进水-> 关闭       ");
				WM_FSM.IN = 0;
			}
		}
		else if(n==3)
		{	
			if(WM_FSM.WM_Mod==0)
			WM_FSM.Wsh++;
	  	sprintf(Apt_MENU[2],"洗涤-> %d分钟  ",WM_FSM.Wsh);
			if(WM_FSM.Wsh==16)
			{
				sprintf(Apt_MENU[2],"洗涤-> 关闭       ");
				WM_FSM.Wsh = 0;
			}
		}
		else if(n==4)
		{
			if(WM_FSM.WM_Mod==0)
			WM_FSM.Dyd++;
			sprintf(Apt_MENU[3],"脱水-> %d分钟  ",WM_FSM.Dyd);
			if(WM_FSM.Dyd==16)
			{
				sprintf(Apt_MENU[3],"脱水-> 关闭       ");
				WM_FSM.Dyd = 0;
			}
		}
		else if(n==5)
		{
			if(WM_FSM.WM_Mod==0)
			WM_FSM.Spin++;
			sprintf(Apt_MENU[4],"甩干-> %d分钟  ",WM_FSM.Spin);
			if(WM_FSM.Spin==16)
			{
				sprintf(Apt_MENU[4],"甩干-> 关闭       ");
				WM_FSM.Spin = 0;
			}
		}
		else if(n==6)
		{
			if(WM_FSM.WM_Mod==0)
			WM_FSM.Dry++;
			sprintf(Apt_MENU[5],"烘干-> %d分钟 ",WM_FSM.Dry);
			if(WM_FSM.Dry==16)
			{
				sprintf(Apt_MENU[5],"烘干-> 关闭       ");
				WM_FSM.Dry = 0;
			}
		}
	}
}

void run(void)
{
	uint8_t TT_Time=WM_FSM.Dry+WM_FSM.Dyd+WM_FSM.IN+WM_FSM.Spin+WM_FSM.Wsh;
	Servo_Init();
	Motor_Init();
	
	OLED_Clear();
	Encoder_Stop();
	WM_FSM.WM_flag = 2;     //进水
	OLED_Printf(0,0,OLED_8X16,"正在执行: ");
	OLED_Printf(0,16,OLED_8X16,"剩余时间: ");
	OLED_Printf(5*16,16,OLED_8X16,"%d分钟  ",TT_Time);
	OLED_Update();
	for(uint8_t i=0;i<WM_FSM.IN;i++)
	{
		Servo_SetAngle(90);
		OLED_Printf(5*16,0,OLED_8X16,"进水");
		OLED_Update();
		for(uint8_t j=0;j<SECONDS;j++)
		{
			for(uint8_t n=0;n<10;n++)
			{
				if(CountSensor_Check(COUNT_UP)||Key_Check(KEY_3,KEY_SINGLE))     // 
				{
					OLED_Printf(0,0,OLED_8X16,"已暂停:   ");
					OLED_Printf(0,2*16,OLED_8X16,"请按确认键继续");
					OLED_Update();
					Servo_SetAngle(0);
					Buzzer_ON();
					while(1)
					{
						if(Key_Check(KEY_3,KEY_SINGLE))
						{
							if(CountSensor_Check(COUNT_HOLD))
							{
								OLED_Printf(0,0,OLED_8X16,"正在执行: ");
				      	OLED_Printf(0,2*16,OLED_8X16,"              ");
				      	OLED_Update();
								Servo_SetAngle(90);
								Key_clearAllFlags();
								CountSensor_clearAllFlags();
								break;
							}
							else
							{
								for(uint8_t i=0;i<10;i++)
								{
									LED2_Turn();
									Delay_ms(200);
								}
							}
						}
					}
				}
				Delay_ms(100);
			}
		}
		TT_Time--;
		OLED_Printf(5*16,16,OLED_8X16,"%d分钟  ",TT_Time);
		OLED_Update();
	}
	Servo_SetAngle(0);
	Delay_ms(2000);
	WM_FSM.WM_flag = 3;  //洗涤
	OLED_Update();
	for(uint8_t i=0;i<WM_FSM.Wsh;i++)
	{
		OLED_Printf(5*16,0,OLED_8X16,"洗涤");
		OLED_Update();
		for(uint8_t j=0;j<SECONDS;j++)
		{
			if(i<WM_FSM.Wsh/2+1)
			{
				if(j%2==0)
				{
					Motor_SetSpeed(50);
					for(uint8_t n=0;n<5;n++)
					{
						if(CountSensor_Check(COUNT_UP)||Key_Check(KEY_3,KEY_SINGLE))     // 
						{
							OLED_Printf(0,0,OLED_8X16,"已暂停:   ");
							OLED_Printf(0,2*16,OLED_8X16,"请按确认键继续");
							OLED_Update();
							Motor_SetSpeed(0);
							Buzzer_ON();
							while(1)
							{
								if(Key_Check(KEY_3,KEY_SINGLE))
								{
									if(CountSensor_Check(COUNT_HOLD))
									{
										OLED_Printf(0,0,OLED_8X16,"正在执行: ");
										OLED_Printf(0,2*16,OLED_8X16,"              ");
										OLED_Update();
										Motor_SetSpeed(50);
										Key_clearAllFlags();
										CountSensor_clearAllFlags();
										break;
									}
									else
									{
										for(uint8_t i=0;i<10;i++)
										{
											LED2_Turn();
											Delay_ms(200);
										}
									}
								}
							}
						}
						Delay_ms(100);
					}
					Motor_SetSpeed(0);
					for(uint8_t n=0;n<5;n++)
					{
            if(CountSensor_Check(COUNT_UP)||Key_Check(KEY_3,KEY_SINGLE))     // 
						{
							OLED_Printf(0,0,OLED_8X16,"已暂停:   ");
							OLED_Printf(0,2*16,OLED_8X16,"请按确认键继续");
							OLED_Update();
							Buzzer_ON();
							while(1)
							{
								if(Key_Check(KEY_3,KEY_SINGLE))
								{
									if(CountSensor_Check(COUNT_HOLD))
									{
										OLED_Printf(0,0,OLED_8X16,"正在执行: ");
										OLED_Printf(0,2*16,OLED_8X16,"              ");
										OLED_Update();
										Key_clearAllFlags();
										CountSensor_clearAllFlags();
										break;
									}
									else
									{
										for(uint8_t i=0;i<10;i++)
										{
											LED2_Turn();
											Delay_ms(200);
										}
									}
								}
							}
						}						
						Delay_ms(100);
					}
				}
				else
				{
					Motor_SetSpeed(-50);
					for(uint8_t n=0;n<5;n++)
					{
						if(CountSensor_Check(COUNT_UP)||Key_Check(KEY_3,KEY_SINGLE))     // 
						{
							OLED_Printf(0,0,OLED_8X16,"已暂停:   ");
							OLED_Printf(0,2*16,OLED_8X16,"请按确认键继续");
							OLED_Update();
							Motor_SetSpeed(0);
							Buzzer_ON();
							while(1)
							{
								if(Key_Check(KEY_3,KEY_SINGLE))
								{
									if(CountSensor_Check(COUNT_HOLD))
									{
										OLED_Printf(0,0,OLED_8X16,"正在执行: ");
										OLED_Printf(0,2*16,OLED_8X16,"              ");
										OLED_Update();
										Motor_SetSpeed(-50);
										Key_clearAllFlags();
										CountSensor_clearAllFlags();
										break;
									}
									else
									{
										for(uint8_t i=0;i<10;i++)
										{
											LED2_Turn();
											Delay_ms(200);
										}
									}
								}
							}
						}
						Delay_ms(100);
					}
					Motor_SetSpeed(0);
					for(uint8_t n=0;n<5;n++)
					{
						if(CountSensor_Check(COUNT_UP)||Key_Check(KEY_3,KEY_SINGLE))     // 
						{
							OLED_Printf(0,0,OLED_8X16,"已暂停:   ");
							OLED_Printf(0,2*16,OLED_8X16,"请按确认键继续");
							OLED_Update();
							Buzzer_ON();
							while(1)
							{
								if(Key_Check(KEY_3,KEY_SINGLE))
								{
									if(CountSensor_Check(COUNT_HOLD))
									{
										OLED_Printf(0,0,OLED_8X16,"正在执行: ");
										OLED_Printf(0,2*16,OLED_8X16,"              ");
										OLED_Update();
										Key_clearAllFlags();
										CountSensor_clearAllFlags();
										break;
									}
									else
									{
										for(uint8_t i=0;i<10;i++)
										{
											LED2_Turn();
											Delay_ms(200);
										}
									}
								}
							}
						}
						Delay_ms(100);
					}
				}
			}
			else
			{
				if(j<(SECONDS/2+SECONDS/3))
				{
					if(i%2==0){
					  Motor_SetSpeed(60);
					}
					else if(i%2==1)
					{
					  Motor_SetSpeed(-60);
					}
					for(uint8_t n=0;n<10;n++)
					{
						if(CountSensor_Check(COUNT_UP)||Key_Check(KEY_3,KEY_SINGLE))     // 
						{
							OLED_Printf(0,0,OLED_8X16,"已暂停:   ");
							OLED_Printf(0,2*16,OLED_8X16,"请按确认键继续");
							OLED_Update();
							Motor_SetSpeed(0);
							Buzzer_ON();
							while(1)
							{
								if(Key_Check(KEY_3,KEY_SINGLE))
								{
									if(CountSensor_Check(COUNT_HOLD))
									{
										OLED_Printf(0,0,OLED_8X16,"正在执行: ");
										OLED_Printf(0,2*16,OLED_8X16,"              ");
										OLED_Update();
										if(i%2==0){
											Motor_SetSpeed(60);
										}
										else if(i%2==1)
										{
											Motor_SetSpeed(-60);
										}
										Key_clearAllFlags();
										CountSensor_clearAllFlags();
										break;
									}
									else
									{
										for(uint8_t i=0;i<10;i++)
										{
											LED2_Turn();
											Delay_ms(200);
										}
									}
								}
							}
						}
						Delay_ms(100);
					}
				}
				else
				{
					Motor_SetSpeed(0);
					for(uint8_t n=0;n<10;n++)
					{
						if(CountSensor_Check(COUNT_UP)||Key_Check(KEY_3,KEY_SINGLE))     // 
						{
							OLED_Printf(0,0,OLED_8X16,"已暂停:   ");
							OLED_Printf(0,2*16,OLED_8X16,"请按确认键继续");
							OLED_Update();
							Buzzer_ON();
							while(1)
							{
								if(Key_Check(KEY_3,KEY_SINGLE))
								{
									if(CountSensor_Check(COUNT_HOLD))
									{
										OLED_Printf(0,0,OLED_8X16,"正在执行: ");
										OLED_Printf(0,2*16,OLED_8X16,"              ");
										OLED_Update();
										Key_clearAllFlags();
										CountSensor_clearAllFlags();
										break;
									}
									else
									{
										for(uint8_t i=0;i<10;i++)
										{
											LED2_Turn();
											Delay_ms(200);
										}
									}
								}
							}
						}
						Delay_ms(100);
					}
				}
			}
		}
		TT_Time--;
		OLED_Printf(5*16,16,OLED_8X16,"%d分钟  ",TT_Time);
		OLED_Update();
	}
	Motor_SetSpeed(0);
	Delay_ms(2000);
	WM_FSM.WM_flag = 4;   //脱水
	OLED_Update();
	for(uint8_t i=0;i<WM_FSM.Dyd;i++)
	{
		Motor_SetSpeed(100);
		OLED_Printf(5*16,0,OLED_8X16,"脱水");
    OLED_Update();		
		for(uint8_t j=0;j<SECONDS;j++)
		{
			for(uint8_t n=0;n<10;n++)
			{
				if(CountSensor_Check(COUNT_UP)||Key_Check(KEY_3,KEY_SINGLE))     // 
					{
						OLED_Printf(0,0,OLED_8X16,"已暂停:   ");
						OLED_Printf(0,2*16,OLED_8X16,"请按确认键继续");
						OLED_Update();
						Motor_SetSpeed(0);
						Buzzer_ON();
						while(1)
						{
							if(Key_Check(KEY_3,KEY_SINGLE))
							{
								if(CountSensor_Check(COUNT_HOLD))
								{
									OLED_Printf(0,0,OLED_8X16,"正在执行: ");
									OLED_Printf(0,2*16,OLED_8X16,"              ");
									OLED_Update();
									Motor_SetSpeed(100);
									Key_clearAllFlags();
									CountSensor_clearAllFlags();
									break;
								}
								else
								{
									for(uint8_t i=0;i<10;i++)
									{
										LED2_Turn();
										Delay_ms(200);
									}
								}
							}
						}
					}
				Delay_ms(100);
			}
		}
		TT_Time--;
		OLED_Printf(5*16,16,OLED_8X16,"%d分钟  ",TT_Time);
		OLED_Update();
	}
	Motor_SetSpeed(0);
	Delay_ms(2000);
	WM_FSM.WM_flag = 5;   //甩干
	OLED_Update();
	for(uint8_t i=0;i<WM_FSM.Spin;i++)
	{
		Motor_SetSpeed(-100);
		OLED_Printf(5*16,0,OLED_8X16,"甩干");
		OLED_Update();
		for(uint8_t j=0;j<SECONDS;j++)
		{
			for(uint8_t n=0;n<10;n++)
			{
				if(CountSensor_Check(COUNT_UP)||Key_Check(KEY_3,KEY_SINGLE))     // 
					{
						OLED_Printf(0,0,OLED_8X16,"已暂停:   ");
						OLED_Printf(0,2*16,OLED_8X16,"请按确认键继续");
						OLED_Update();
						Motor_SetSpeed(0);
						Buzzer_ON();
						while(1)
						{
							if(Key_Check(KEY_3,KEY_SINGLE))
							{
								if(CountSensor_Check(COUNT_HOLD))
								{
									OLED_Printf(0,0,OLED_8X16,"正在执行: ");
									OLED_Printf(0,2*16,OLED_8X16,"              ");
									OLED_Update();
									Motor_SetSpeed(-100);
									Key_clearAllFlags();
									CountSensor_clearAllFlags();
									break;
								}
								else
								{
									for(uint8_t i=0;i<10;i++)
									{
										LED2_Turn();
										Delay_ms(200);
									}
								}
							}
						}
					}
				Delay_ms(100);
			}
		}
		TT_Time--;
		OLED_Printf(5*16,16,OLED_8X16,"%d分钟  ",TT_Time);
		OLED_Update();
	}
	Motor_SetSpeed(0);
	Delay_ms(2000);
	WM_FSM.WM_flag = 6;   //烘干
	OLED_Update();
	for(uint8_t i=0;i<WM_FSM.Dry;i++)
	{
		LED1_ON();
		OLED_Printf(5*16,0,OLED_8X16,"烘干");
		OLED_Update();
		for(uint8_t j=0;j<SECONDS;j++)
		{
			for(uint8_t n=0;n<10;n++)
			{
				if(CountSensor_Check(COUNT_UP)||Key_Check(KEY_3,KEY_SINGLE))     // 
					{
						OLED_Printf(0,0,OLED_8X16,"已暂停:   ");
						OLED_Printf(0,2*16,OLED_8X16,"请按确认键继续");
						OLED_Update();
						LED1_OFF();
						Buzzer_ON();
						while(1)
						{
							if(Key_Check(KEY_3,KEY_SINGLE))
							{
								if(CountSensor_Check(COUNT_HOLD))
								{
									OLED_Printf(0,0,OLED_8X16,"正在执行: ");
									OLED_Printf(0,2*16,OLED_8X16,"              ");
									OLED_Update();
									LED1_ON();
									Key_clearAllFlags();
									CountSensor_clearAllFlags();
									break;
								}
								else
								{
									for(uint8_t i=0;i<10;i++)
									{
										LED2_Turn();
										Delay_ms(200);
									}
								}
							}
						}
					}
				Delay_ms(100);
			}
		}
		TT_Time--;
		OLED_Printf(5*16,16,OLED_8X16,"%d分钟  ",TT_Time);
		OLED_Update();
	}
	LED1_OFF();
	Delay_ms(2000);
	WM_FSM.WM_flag = 7;   //已完成
	OLED_Clear();
	LED4_ON();
	Buzzer_ON();
	OLED_Printf(0,0,OLED_8X16,"已完成...");
	OLED_Printf(0,16,OLED_8X16,"请按确认键返回");
	OLED_Update();
	while(1)
	{
		if(Key_Check(KEY_3,KEY_SINGLE))
		{
			LED4_OFF();
			Apt_Dish(7);
			Encoder_Continue();
			MENU();
		}
	}
}









void appointment(void)
{
	OLED_Clear();
	OLED_Update();
	WM_FSM.WM_flag = 1;
	uint8_t make_time[3]={0,0,0};
	uint32_t clock_time = 0;
	strcpy(Apt_make[0],"时->   0  ");
	strcpy(Apt_make[1],"分->   0  ");
	strcpy(Apt_make[2],"秒->   0  ");
	uint8_t n;
	while(1)
	{
		n = Apt_CFM(Apt_make,5);
		if(n==1)
		{
			make_time[0]++;
			if(make_time[0]==24)
			{
				make_time[0] = 0;
			}
			sprintf(Apt_make[0],"时->   %d  ",make_time[0]);
		}
		else if(n==2)
		{
			make_time[1]++;
			if(make_time[1]==60)
			{
				make_time[1] = 0;
			}
			sprintf(Apt_make[1],"分->   %d  ",make_time[1]);
		}
		else if(n==3)
		{
			make_time[2]++;
			if(make_time[2]==60)
			{
				make_time[2] = 0;
			}
			sprintf(Apt_make[2],"秒->   %d  ",make_time[2]);
		}
		else if(n==4)
		{
			Key_clearAllFlags();
			CountSensor_clearAllFlags();
			clock_time = make_time[0]*60*60+make_time[1]*60+make_time[2];
			MyRTC_SetTime(clock_time);
			Apt_Dish(1);
			if(clock_time!=0)
			LED3_ON();
			MENU();
		}
		else if(n==5)
		{
			Key_clearAllFlags();
			CountSensor_clearAllFlags();
			Apt_Dish(1);
			MENU();
		}
	}
}

void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
	{
		Key_Tick();
		CountSensor_Tick();
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}
void RTCAlarm_IRQHandler(void)
{
	if(RTC_GetITStatus(RTC_IT_ALR)!=RESET)
	{
	   if(WM_FSM.WM_flag==0)
		 {
			 WM_FSM.make=1;
		 }
		 else
		 {
			 LED3_OFF();
		 }
	}
	RTC_ClearITPendingBit(RTC_IT_ALR);
	EXTI_ClearITPendingBit(EXTI_Line17);
}
