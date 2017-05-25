/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2014        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "diskio.h"		// FatFs lower layer API
#include "bsp_w25qxx.h"

/* Definitions of physical drive number for each drive */
/* 为每一个物理的磁盘分配盘符(编号) */
#define SPI_FLASH       0

/**
 * @Description         Get Drive Status 
 * @param pdrv          Physical drive nmuber to identify the drive
 * @return DSTATUS
 */
DSTATUS disk_status(BYTE pdrv)
{
        DSTATUS stat;

        switch(pdrv)
        {
        case SPI_FLASH:
                if(W25QXX_ReadID() == W25Q128)
                {
                        /* STA_OK 这个宏并没有，是我自己添加的，其实就就是0 */
                        stat = STA_OK;
                }
                else
                {
                        stat = STA_NOINIT;
                }
                return stat;

        }
        return STA_NOINIT;
}

/**
 * @Description         Inidialize a Drive
 * @param pdrv          Physical drive nmuber to identify the drive
 * @return DSTATUS
 */
DSTATUS disk_initialize(BYTE pdrv)
{
        DSTATUS stat;

        switch(pdrv)
        {
        case SPI_FLASH:
                W25QXX_Init();
                /* 有可能进入了掉电模式，这样的就无法进行读写擦除一系列操作了 */
                W25QXX_WakeUp();
                stat = disk_status(SPI_FLASH);
                /* 打印初始化返回状态码 */
                printf("diskio:\t\tFlash Init Status = %d\r\n\r\n", stat);
                return stat;

        }
        return STA_NOINIT;
}

/**
 * @Description         Read Sector(s)
 * @param pdrv          Physical drive nmuber to identify the drive
 * @param buff          Data buffer to store read data 
 * @param sector        Sector address in LBA 
 * @param count         Number of sectors to read 
 * @return DRESULT      
 */
DRESULT disk_read(BYTE pdrv, BYTE *buff, DWORD sector, UINT count)
{
        DRESULT res;

        switch(pdrv)
        {
        case SPI_FLASH:
                W25QXX_Read(buff, sector * 512, count * 512);
                res = RES_OK;
                return res;

        }

        return RES_PARERR;
}

/**
 * @Description         Write Sector(s) 
 * @param pdrv          Physical drive nmuber to identify the drive
 * @param buff          Data to be written 
 * @param sector        Sector address in LBA 
 * @param count         Number of sectors to write 
 * @return DRESULT      
 */
#if _USE_WRITE
DRESULT disk_write(BYTE pdrv, const BYTE *buff, DWORD sector, UINT count)
{
        DRESULT res;

        switch(pdrv)
        {
        case SPI_FLASH:
                /* 一定要先擦除再写入 */
                W25QXX_Write((u8*) buff, sector * 512, count * 512);
                res = RES_OK;
                return res;

        }

        return RES_PARERR;
}
#endif

/**
 * @Description         Miscellaneous Functions  
 * @param pdrv          Physical drive nmuber (0..)
 * @param cmd           Control code
 * @param buff          Buffer to send/receive control data
 * @return DRESULT      
 */
#if _USE_IOCTL
DRESULT disk_ioctl(BYTE pdrv, BYTE cmd, void *buff)
{
        DRESULT res;

        switch(pdrv)
        {
        case SPI_FLASH:
                switch(cmd)
                {
                case GET_SECTOR_COUNT:                  // 返回扇区个数
                        *(DWORD*) buff = 32768;         // 16MB/512B = 32768
                        break;
                case GET_SECTOR_SIZE:
                        *(WORD*) buff = 512;            // 返回每个扇区大小4KB
                        break;
                case GET_BLOCK_SIZE:                    // 返回擦除扇区的最小个数(单位为扇区)
                        *(WORD*) buff = 1;
                        break;
                }
                return res;
        }

        return RES_PARERR;
}
#endif

/**
 * @Descripiton         Gets the current time
 * @return DWORD        current time
 */
DWORD get_fattime(void)
{
        return 0;
}

