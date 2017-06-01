#ifndef __DRIVER_SRAM_H_
#define __DRIVER_SRAM_H_

#include "stm32f4xx.h"
#include "explore_usart.h"

/*使用NOR/SRAM的 Bank1.sector3,地址位HADDR[27,26]=10*/
/*对IS61LV25616/IS62WV25616,地址线范围为A0~A17*/
/*对IS61LV51216/IS62WV51216,地址线范围为A0~A18*/
#define Bank1_SRAM3_ADDR ((u32)(0x68000000))

void Sram_Init(void);
void Sram_WriteBuffer(u8* pBuffer, u32 WriteAddr, u32 NumHalfwordToWrite);
void Sram_ReadBuffer(u8* pBuffer, u32 ReadAddr, u32 NumHalfwordToRead);

#endif /*__DRIVER_SRAM_H_*/
