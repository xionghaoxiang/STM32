#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Key.h"

#define Menu_Speed 2;  //菜单滑行速度最快8最低1只能是2的倍数或1
#define Cursor_Speed 1; //光标滑行速度最快2最低1
/*
char **Apt :传入一个char类型的指针数组用于存放菜单 例如一个4选项的菜单：char *Apt[4]={"dsf","fd","dfds","dfs"};
AptNum : 菜单选项的数目 例如上例就是4
返回值 ： 当确认按键按下时返回光标所指的菜单编号，没按下时返回0
KE_1:下一个;；
KE_2: 上一个；
KE_3; 确认；
*/
uint8_t Dish=1;
uint8_t Key_Num;
uint8_t Dish_Num=1,w,i;//w控制菜单平滑移动不用管i控制光标
void Apt_Dish(uint8_t n ) //修改初始光标选项
{
	Dish = n;
	Dish_Num = n;
}
uint8_t Apt_CFM(char Apt[][50],uint8_t AptNum) 
{

	uint8_t Conf=0;
	i=(Dish_Num-1)*16;
	
  if(Key_Check(KEY_1,KEY_SINGLE)||Key_Check(KEY_1,KEY_REPEAT)) 
	{
		Dish++;
		Dish_Num++;
		Key_Num = 1;
		if(Dish_Num>4&&AptNum>4)w=16;
		if(Dish>AptNum&&AptNum>4)
		{
			OLED_Clear();
		}
		else if(Dish>4&&AptNum>4&&Dish_Num==5)
		{
			OLED_Clear();
		}
	}
	 if(Key_Check(KEY_2,KEY_SINGLE)||Key_Check(KEY_2,KEY_REPEAT)) 
	{
		Dish--;
		Dish_Num--;
		Key_Num = 2;
		if(Dish_Num<1&&AptNum>4)	w=16;
		if(Dish==0&&AptNum>4)
		{
			OLED_Clear();
		}
		else if(AptNum>4&&Dish_Num==0)
		{
			OLED_Clear();
		}
	}
	if(Dish_Num>4&&AptNum>4) Dish_Num=4;
	else if(Dish_Num<1&&AptNum>4) Dish_Num=1;
	if(Dish>AptNum) 
	{
		Dish  = 1;
		OLED_Printf(0,(AptNum-1)*16,OLED_8X16,"  ");
		Dish_Num = 1;
	}
	else if(Dish<=0)
	{
		if(Dish==0){
	    Dish = AptNum;
	 	  Dish_Num = AptNum;
		  if(Dish_Num>4) Dish_Num=4;
		  OLED_Printf(0,(1-1)*16,OLED_8X16,"  ");
		}
		else
		{
			Dish_Num=1;
		}
	}
  if(i ==(Dish_Num-1)*16)
	OLED_Printf(0,(Dish_Num-1)*16,OLED_8X16,"->");   //光标
	while(i!=(Dish_Num-1)*16)
	{
		if(i<(Dish_Num-1)*16){
		  i+=Cursor_Speed;
			if(i>(Dish_Num-1)*16) i=(Dish_Num-1)*16;
		  OLED_Printf(0,i,OLED_8X16,"->"); 
		  OLED_UpdateArea(0,i,16,i+16);
		  Delay_ms(10);
		}
		else
		{
			i-=Cursor_Speed;
			if(i<(Dish_Num-1)*16) i=(Dish_Num-1)*16;
		  OLED_Printf(0,i,OLED_8X16,"->"); 
		  OLED_UpdateArea(0,i,16,i+16);
		  Delay_ms(10);
		}

	}
	
  if(AptNum==1)
	{
		OLED_Printf(2*8,0*16,OLED_8X16,Apt[0]);
		OLED_Update();
	}
	else if(AptNum==2)
	{
		OLED_Printf(2*8,0*16,OLED_8X16,Apt[0]);
    OLED_Printf(2*8,1*16,OLED_8X16,Apt[1]);
		OLED_Update();
	}
	else if(AptNum==3)
	{
		OLED_Printf(2*8,0*16,OLED_8X16,Apt[0]);
    OLED_Printf(2*8,1*16,OLED_8X16,Apt[1]);
    OLED_Printf(2*8,2*16,OLED_8X16,Apt[2]);
		OLED_Update();
	}
	else if(AptNum>=4)
	{
		if(w==16&&Dish_Num==4){
			while(w!=0){
				w-=Menu_Speed;
				if(w<0) w=0;
				OLED_Printf(2*8,w-16,OLED_8X16,Apt[Dish-5]);
	 	   	OLED_Printf(2*8,w+0*16,OLED_8X16,Apt[Dish-4]);
       	OLED_Printf(2*8,w+1*16,OLED_8X16,Apt[Dish-3]);
       	OLED_Printf(2*8,w+2*16,OLED_8X16,Apt[Dish-2]);
       	OLED_Printf(2*8,w+3*16,OLED_8X16,Apt[Dish-1]);
	    	OLED_Update();
			}
		}
		else if(w!=16&&Dish_Num==4)
		{
		 OLED_Printf(2*8,0*16,OLED_8X16,Apt[Dish-4]);
     OLED_Printf(2*8,1*16,OLED_8X16,Apt[Dish-3]);
     OLED_Printf(2*8,2*16,OLED_8X16,Apt[Dish-2]);
     OLED_Printf(2*8,3*16,OLED_8X16,Apt[Dish-1]);
 		 OLED_Update();
		}
			
		else if(w!=16&&Dish_Num==3)
		{
			OLED_Printf(2*8,0*16,OLED_8X16,Apt[Dish-3]);
			OLED_Printf(2*8,1*16,OLED_8X16,Apt[Dish-2]);
			OLED_Printf(2*8,2*16,OLED_8X16,Apt[Dish-1]);
      OLED_Printf(2*8,3*16,OLED_8X16,Apt[Dish]);
	  	OLED_Update();
		}
		else if(w!=16&&Dish_Num==2)
		{
			OLED_Printf(2*8,0*16,OLED_8X16,Apt[Dish-2]);
      OLED_Printf(2*8,1*16,OLED_8X16,Apt[Dish-1]);
      OLED_Printf(2*8,2*16,OLED_8X16,Apt[Dish]);
      OLED_Printf(2*8,3*16,OLED_8X16,Apt[Dish+1]);
			OLED_Update();
		}
		else if(w!=16&&Dish_Num==1)
		{
		  OLED_Printf(2*8,0*16,OLED_8X16,Apt[Dish-1]);
      OLED_Printf(2*8,1*16,OLED_8X16,Apt[Dish]);
      OLED_Printf(2*8,2*16,OLED_8X16,Apt[Dish+1]);
      OLED_Printf(2*8,3*16,OLED_8X16,Apt[Dish+2]);
	    OLED_Update();
		}
  	else if(w==16&&Dish_Num==1)
  	{
		  while(w!=0)
			{
			  w-=Menu_Speed;
				if(w<0) w=0;
 	      OLED_Printf(2*8,0*16-w,OLED_8X16,Apt[Dish-1]);
        OLED_Printf(2*8,1*16-w,OLED_8X16,Apt[Dish]);
        OLED_Printf(2*8,2*16-w,OLED_8X16,Apt[Dish+1]);
				OLED_Printf(2*8,3*16-w,OLED_8X16,Apt[Dish+2]);
			  OLED_Printf(2*8,4*16-w,OLED_8X16,Apt[Dish+3]);
	      OLED_Update();
		  }
	  }
  }
	
	if(Key_Num==1&&Dish_Num>=2)
	{
		Key_Num=0;
    OLED_Printf(0,(Dish_Num-2)*16,OLED_8X16,"  ");
    OLED_Update();
	}
	if(Key_Num==2&&Dish_Num>=0)
	{
		Key_Num = 0;
    OLED_Printf(0,(Dish_Num)*16,OLED_8X16,"  ");
    OLED_Update();
	}
	if((Key_Check(KEY_3,KEY_SINGLE)||Key_Check(KEY_3,KEY_REPEAT))&&Dish_Num>=1)
	{
		Conf = Dish;
  	OLED_Printf(0,(Dish_Num-1)*16,OLED_8X16,"  ");
	}
	return Conf;
}

