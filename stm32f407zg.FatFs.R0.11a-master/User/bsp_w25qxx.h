#ifndef __BSP_W25QXX_H
#define __BSP_W25QXX_H

#include "stm32f4xx.h"
#include "bsp_systick.h"
#include "bsp_usart.h"
#include "bsp_spi.h"

/* W25X系列/Q系列芯片列表 */
#define W25Q80  0xEF13
#define W25Q16  0xEF14
#define W25Q32  0xEF15
#define W25Q64  0xEF16
#define W25Q128 0xEF17

/* 记录W25QXX芯片型号的变量 */
extern u16 W25QXX_TYPE;

/* W25QXX的片选信号，其实就是SPI的片选信号 */
#define	W25QXX_CS PBout(14)

/* W25Q128指令表 */
#define W25X_WriteEnable	0x06
#define W25X_WriteDisable	0x04
#define W25X_ReadStatusReg	0x05
#define W25X_WriteStatusReg	0x01
#define W25X_ReadData		0x03
#define W25X_FastReadData	0x0B
#define W25X_FastReadDual	0x3B
#define W25X_PageProgram	0x02
#define W25X_BlockErase		0xD8
#define W25X_SectorErase	0x20
#define W25X_ChipErase		0xC7
#define W25X_PowerDown		0xB9
#define W25X_ReleasePowerDown	0xAB
#define W25X_DeviceID		0xAB
#define W25X_ManufactDeviceID	0x90
#define W25X_JedecDeviceID	0x9F

void W25QXX_Init(void);                                                 // Flash初始化
u16 W25QXX_ReadID(void);                                                // 读取Flash ID
u8 W25QXX_ReadSR(void);                                                 // 读取状态寄存器
void W25QXX_WriteSR(u8 state);                                          // 写状态寄存器
void W25QXX_WriteEnable(void);                                          // 写使能
void W25QXX_WriteDisable(void);                                         // 写保护
void W25QXX_WriteNoCheck(u8* pBuffer, u32 address, u16 length);         // 写入flash(不带擦除)
void W25QXX_Read(u8* pBuffer, u32 address, u16 length);                 // 读取flash
void W25QXX_Write(u8* pBuffer, u32 address, u16 length);                // 写入flash(带擦除)
void W25QXX_EraseChip(void);                                            // 整片擦除
void W25QXX_EraseSector(u32 Dst_Addr);                                  // 扇区擦除
void W25QXX_WaitBusy(void);                                             // 等待空闲
void W25QXX_PowerDown(void);                                            // 进入掉电模式
void W25QXX_WakeUp(void);                                               // 唤醒

#endif /* __BSP_W25QXX_H */
