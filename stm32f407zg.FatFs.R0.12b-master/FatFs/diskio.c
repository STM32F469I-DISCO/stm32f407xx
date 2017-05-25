#include "diskio.h"
#include "bsp_w25qxx.h"
#include "stm32f4xx.h"

/* 为每一个物理的磁盘分配盘符(编号) */
#define DEV_FLASH       0       // SPI FLASH
#define DEV_SRAM        1       // FSMC SRAM
#define DEV_SDCard      2       // SDIO SDCard
#define DEV_USB         3       // USB

/**
 * @Description 
 * @param 
 * @param 
 * @param 
 */
DSTATUS disk_status(BYTE pdrv)
{
        DSTATUS stat;

        switch(pdrv)
        {
        case DEV_FLASH:
                if(W25QXX_ReadID() == W25Q128)
                {
                        stat = STA_OK;
                        printf("diskio:\t\tFlash Init Status = %d\r\n\r\n", stat);
                }
                else
                {
                        stat = STA_NOINIT;
                }
                return stat;

        case DEV_SRAM:
                return stat;

        case DEV_SDCard:
                return stat;

        case DEV_USB:
                return stat;

        }
        return STA_NOINIT;
}

/**
 * @Description 
 * @param 
 * @param 
 * @param 
 */
DSTATUS disk_initialize(BYTE pdrv)
{
        DSTATUS stat;

        switch(pdrv)
        {
        case DEV_FLASH:
                W25QXX_Init();
                W25QXX_WakeUp();
                stat = disk_status(DEV_FLASH);
                return stat;
        case DEV_SRAM:
                return stat;

        case DEV_SDCard:
                return stat;

        case DEV_USB:
                return stat;
        }
        return STA_NOINIT;
}

/**
 * @Description 
 * @param 
 * @param 
 * @param 
 */
DRESULT disk_read(BYTE pdrv, BYTE *buff, DWORD sector, UINT count)
{
        DRESULT res;

        switch(pdrv)
        {
        case DEV_FLASH:
                W25QXX_Read(buff, sector * 4096, count * 4096);
                res = RES_OK;
                return res;

        case DEV_SRAM:
                return res;

        case DEV_SDCard:
                return res;

        case DEV_USB:
                return res;
        }

        return RES_PARERR;
}

/**
 * @Description 
 * @param 
 * @param 
 * @param 
 */
DRESULT disk_write(BYTE pdrv, const BYTE *buff, DWORD sector, UINT count)
{
        DRESULT res;

        switch(pdrv)
        {
        case DEV_FLASH:
                W25QXX_Write((u8*) buff, sector * 4096, count * 4096);
                res = RES_OK;
                return res;

        case DEV_SRAM:
                return res;

        case DEV_SDCard:
                return res;

        case DEV_USB:
                return res;
        }

        return RES_PARERR;
}

/**
 * @Description 
 * @param 
 * @param 
 * @param 
 */
DRESULT disk_ioctl(BYTE pdrv, BYTE cmd, void *buff)
{
        DRESULT res;

        switch(pdrv)
        {
        case DEV_FLASH:
                switch(cmd)
                { 
			case GET_SECTOR_COUNT:                  // 返回扇区个数
				*(DWORD*)buff = 4096;           // 16MB/4KB
                                break;
			case GET_SECTOR_SIZE:
				*(WORD*)buff = 4096;            // 返回每个扇区大小4KB
                                break;
			case GET_BLOCK_SIZE:                    // 返回擦除扇区的最小个数(单位为扇区)
                                *(WORD*)buff = 1;
			break;
                }
                return res;
                
        case DEV_SRAM:
                return res;

        case DEV_SDCard:
                return res;

        case DEV_USB:
                return res;
        }

        return RES_PARERR;
}

/**
 * @Description  
 */
DWORD get_fattime(void)
{
        return 0;
}
