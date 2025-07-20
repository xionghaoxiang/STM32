#include "stm32f10x.h"
#include <time.h>
#include "MyRTC.h"
uint16_t MyRTC_time[]= {2025,7,20,11,9,55};

void MyRTC_Init(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR,ENABLE);
    
    PWR_BackupAccessCmd(ENABLE);
    if (BKP_ReadBackupRegister(BKP_DR1) != 0xA5A5)
    {
    RCC_LSEConfig(RCC_LSE_ON);
    while( RCC_GetFlagStatus(RCC_FLAG_LSERDY) != SET );

    RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
    RCC_RTCCLKCmd(ENABLE);

    RTC_WaitForSynchro();
    RTC_WaitForLastTask();

    RTC_SetPrescaler(32768-1);
    RTC_WaitForLastTask();

    MyRTC_Settime();
    BKP_WriteBackupRegister(BKP_DR1,0xA5A5);
    }
    else 
    {
    RTC_WaitForSynchro();
    RTC_WaitForLastTask();        
    }



}
void MyRTC_Settime(void)
{
    time_t time_cnt;
    struct tm time_data;
    time_data.tm_year = MyRTC_time[0]-1900;
    time_data.tm_mon = MyRTC_time[1]-1;
    time_data.tm_mday = MyRTC_time[2];
    time_data.tm_hour = MyRTC_time[3];
    time_data.tm_min = MyRTC_time[4];
    time_data.tm_sec = MyRTC_time[5];
    
    time_cnt = mktime(&time_data)-8*60*60;

    RTC_SetCounter(time_cnt);
}
void MyRTC_Readtime(void)
{
    time_t time_cnt;
    struct tm time_data; 
    
    time_cnt = RTC_GetCounter()+8*60*60;
    time_data = *localtime(&time_cnt);
    MyRTC_time[0] = time_data.tm_year + 1900;
    MyRTC_time[1] = time_data.tm_mon +1;
    MyRTC_time[2] = time_data.tm_mday ;
    MyRTC_time[3] = time_data.tm_hour ;
    MyRTC_time[4] = time_data.tm_min  ;
    MyRTC_time[5] = time_data.tm_sec  ;    

}
