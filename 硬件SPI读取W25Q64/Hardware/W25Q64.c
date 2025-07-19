#include "stm32f10x.h"
#include "MySPI.h"
#include "W25Q64_Ins.h"
void W25Q64_Init(void)
{
    MySPI_Init();
}
void W25Q64_ReadID(uint8_t *MID ,uint16_t *DID)
{   
    MySPI_Start();
    MySPI_SwapByte(W25Q64_JEDEC_ID);
    *MID = MySPI_SwapByte(W25Q64_DUMMY_BYTE);
    *DID = MySPI_SwapByte(W25Q64_DUMMY_BYTE);
    *DID <<= 8 ;
    *DID |= MySPI_SwapByte(W25Q64_DUMMY_BYTE);
    MySPI_Stop();
}
void W25Q64_WriteEnable(void)
{
    MySPI_Start();
    MySPI_SwapByte(W25Q64_WRITE_ENABLE);
    MySPI_Stop();
}
void W25Q64_WaitBusy(void)
{
    uint32_t time_out = 10000;
    MySPI_Start();
    MySPI_SwapByte(W25Q64_READ_STATUS_REGISTER_1);
    while(MySPI_SwapByte(W25Q64_WRITE_ENABLE) & 0x01 == 0x01) 
    {
        time_out--;
        if (time_out ==0)
        {
            break;
        }
    }

    MySPI_Stop();
}
void W25Q64_PageProgram(uint32_t Address , uint8_t  *dataArray, uint16_t count)
{
    W25Q64_WriteEnable();
    MySPI_Start();
    MySPI_SwapByte(W25Q64_PAGE_PROGRAM);
    MySPI_SwapByte(Address >>16 );
    MySPI_SwapByte(Address >> 8);
    MySPI_SwapByte(Address);
    for (uint16_t i = 0; i<count ; i++)
    {
        MySPI_SwapByte(dataArray[i]);
    }
    MySPI_Stop();

    W25Q64_WaitBusy();
    
}
void W25Q64_SectorErase(uint32_t Address)
{   
    W25Q64_WriteEnable();
    MySPI_Start();
    MySPI_SwapByte(W25Q64_SECTOR_ERASE_4KB);
    MySPI_SwapByte(Address >>16 );
    MySPI_SwapByte(Address >> 8);
    MySPI_SwapByte(Address);
    MySPI_Stop();

    W25Q64_WaitBusy();
}
void W25Q64_ReadData(uint32_t Address, uint8_t  *dataArray, uint32_t count)
{
    MySPI_Start();
    MySPI_SwapByte(W25Q64_READ_DATA);
    MySPI_SwapByte(Address >>16 );
    MySPI_SwapByte(Address >> 8);
    MySPI_SwapByte(Address);
    for (uint32_t i = 0; i<count ;i++)
    {
        dataArray[i] = MySPI_SwapByte(W25Q64_WRITE_ENABLE);
    }
    MySPI_Stop();
}