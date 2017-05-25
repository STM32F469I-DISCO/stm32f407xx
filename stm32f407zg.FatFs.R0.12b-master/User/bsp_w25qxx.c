#include "bsp_w25qxx.h"

/* 驱动版本号：bsp_w25qxx v1.4 */

u16 W25QXX_TYPE = 0;

/**
 * W25Q128简介，128Mbit = 16MB Flash
 * Flash分成256个Block(块)，每个块大小64KB
 * Block分成16个Sector(扇区)，每个扇区大小4KB
 * 擦除的最小单位是扇区
 */

/**
 * @Description 初始化FLASH
 */
void W25QXX_Init(void)
{
        GPIO_InitTypeDef GPIO_InitStructure;

        /* 第一步：时钟使能 */
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);

        /* 第二步：配置W25Q128片选信号GPIO模式，PB14 */
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
        GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
        GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
        GPIO_Init(GPIOB, &GPIO_InitStructure);

        /* 配置NRF_CS片选信号模式，PG7 */
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
        GPIO_Init(GPIOG, &GPIO_InitStructure);

        /* 第三步：配置SPI片选信号 */
        /* 片选不选NRF，防止NRF干扰SPI和FLASH的通信，因为NRF也是挂在此SPI上 */
        GPIO_SetBits(GPIOG, GPIO_Pin_7);

        /* 片选也不选FLASH，因为要先初始化 */
        W25QXX_CS = 1;

        /* 初始化SPI */
        Spi_Init();

        /* 设置为21M时钟，高速模式，4分频，84/4=21 */
        Spi_SetSpeed(SPI_BaudRatePrescaler_4);

        /* 读取FLASH ID */
        W25QXX_TYPE = W25QXX_ReadID();
        printf("bsp_w25qxx:\tFlash ID = %x \r\n", W25QXX_TYPE);

        if(W25QXX_TYPE == W25Q128)
        {
                printf("bsp_w25qxx:\tFlash Chip Type is W25Q128\r\n\r\n");
        }
}

/**
 * @Description 读取W25QXX的状态寄存器
 * @return u8   读取到的状态值
 */
u8 W25QXX_ReadSR(void)
{
        u8 byte = 0;

        /* 片选选中 */
        W25QXX_CS = 0;

        /* 写指令后读取状态 */
        Spi_ReadWriteByte(W25X_ReadStatusReg);
        byte = Spi_ReadWriteByte(0xff);

        /* 片选释放 */
        W25QXX_CS = 1;

        return byte;
}

/**
 * @Description 写W25QXX状态寄存器
 * @notice 只有SPR,TB,BP2,BP1,BP0(bit 7,5,4,3,2)可以写
 */
void W25QXX_WriteSR(u8 state)
{
        /* 片选选中 */
        W25QXX_CS = 0;

        /* 写指令后写状态 */
        Spi_ReadWriteByte(W25X_WriteStatusReg);
        Spi_ReadWriteByte(state);

        /* 片选释放 */
        W25QXX_CS = 1;
}

/**
 * @Description W25QXX写使能，将WEL置位
 */
void W25QXX_WriteEnable(void)
{
        /* 片选选中 */
        W25QXX_CS = 0;

        /* 发送写使能指令 */
        Spi_ReadWriteByte(W25X_WriteEnable);

        /* 片选释放 */
        W25QXX_CS = 1;
}

/**
 * @Description W25QXX写禁止，将WEL清零
 */
void W25QXX_WriteDisable(void)
{
        /* 片选选中 */
        W25QXX_CS = 0;

        /* 发送写禁止指令 */
        Spi_ReadWriteByte(W25X_WriteDisable);

        /* 片选释放 */
        W25QXX_CS = 1;
}

/**
 * @Discription 读取芯片ID
 * @return u16  芯片ID
 */
u16 W25QXX_ReadID(void)
{
        /* 用来记录芯片ID的变量 */
        u16 temp = 0;

        /* 片选选中 */
        W25QXX_CS = 0;

        /* 发送读取ID命令0x90000000 */
        Spi_ReadWriteByte(0x90);
        Spi_ReadWriteByte(0x00);
        Spi_ReadWriteByte(0x00);
        Spi_ReadWriteByte(0x00);

        /* 读取芯片的ID */
        temp |= Spi_ReadWriteByte(0xff) << 8;
        temp |= Spi_ReadWriteByte(0xff);

        /* 片选释放 */
        W25QXX_CS = 1;

        return temp;
}

/**
 * @Description 读取SPI FLASH，在指定地址开始读取指定长度的数据
 * @param pBuffer 数据存储区（通过指针返回读取值）
 * @param address 开始读取的地址(24bit对应为16M)
 * @param length  要读取的字节数(最大65535)
 */
void W25QXX_Read(u8* pBuffer, u32 address, u16 length)
{
        u16 i;

        /* 片选选中 */
        W25QXX_CS = 0;

        /* 发送读取命令 */
        Spi_ReadWriteByte(W25X_ReadData);
        /* 发送24bit地址 */
        Spi_ReadWriteByte((u8)((address) >> 16));
        Spi_ReadWriteByte((u8)((address) >> 8));
        Spi_ReadWriteByte((u8) address);

        /* 通过指针返回读取值 */
        for(i = 0; i < length; i++)
        {
                pBuffer[i] = Spi_ReadWriteByte(0xff);
        }

        /* 片选释放 */
        W25QXX_CS = 1;
}

/**
 * @Description SPI在一页内写入少于256个字节的数据
 * @param pBuffer 数据存储区
 * @param address 开始写入的地址(24bit)
 * @param length  要写入的字节数(最大256)，该数不应该超过该页的剩余字节数
 * @notice 必须确保所写的地址范围内的数据全部为0xff，否则在非0xff处写入的数据将失败
 */
void W25QXX_WritePage(u8* pBuffer, u32 address, u16 length)
{
        /* 循环变量 */
        u16 i;

        /* 写使能 */
        W25QXX_WriteEnable();

        /* 片选选中 */
        W25QXX_CS = 0;

        /* 发送写页命令 */
        Spi_ReadWriteByte(W25X_PageProgram);

        /* 发送24bit地址 */
        Spi_ReadWriteByte((u8)((address) >> 16));
        Spi_ReadWriteByte((u8)((address) >> 8));
        Spi_ReadWriteByte((u8) address);

        /* 循环写数 */
        for(i = 0; i < length; i++)
        {
                Spi_ReadWriteByte(pBuffer[i]);
        }

        /* 片选释放 */
        W25QXX_CS = 1;

        /* 等待写入结束 */
        W25QXX_WaitBusy();
}

/**
 * @Description 在指定地址开始写入指定长度的数据，具有自动换页功能
 * @param pBuffer 数据存储区
 * @param address 开始写入的地址(24bit)
 * @param length  要写入的字节数(最大65535)
 * @notice 必须确保所写的地址范围内的数据全部为0xff，否则在非0xff处写入的数据将失败
 */
void W25QXX_WriteNoCheck(u8* pBuffer, u32 address, u16 length)
{
        /* 单页剩余的字节数 */
        u16 pageremain = 256 - address % 256;

        /* 如果本页剩余的空间就可以存放要写的数据 */
        if(length <= pageremain)
        {
                /* 则直接写本页就可以 */
                W25QXX_WritePage(pBuffer, address, length);
        }
        else
        {
                /* 如果本页剩余的空间不够，就要跨页写入，现将本页写满 */
                while(1)
                {
                        /* 写完本页要写入的空间 */
                        W25QXX_WritePage(pBuffer, address, pageremain);

                        /* 数据写了一部分了，将没有写的数据偏移到缓冲区最开始 */
                        pBuffer = pBuffer + pageremain;

                        /* 数据写了一部分了，将地址设置为下一页首地址 */
                        address = address + pageremain;

                        /* 数据剩余的长度为原来长度减去已经写入了的字节数 */
                        length = length - pageremain;

                        /* 如果剩余的长度仍然要跨页 */
                        if(length > 256)
                        {
                                /* 则设置下一页全部空间256均为要写入的空间 */
                                pageremain = 256;
                        }
                        else
                        {
                                /* 则设置下一页前length长度的空间为要写入的空间 */
                                pageremain = length;
                        }

                        if(length == 0)
                        {
                                break;
                        }
                };
        }
}

u8 W25QXX_BUFFER[4096];

/**
 * @Description 在指定地址开始写入指定长度的数据，具有自动换页功能，该函数带擦除操作
 * @param pBuffer 数据存储区
 * @param address 开始写入的地址(24bit)
 * @param length  要写入的字节数
 */
void W25QXX_Write(u8* pBuffer, u32 address, u16 length)
{
        /*扇区地址*/
        u32 secpos = address / 4096;

        /*在扇区内的偏移*/
        u16 secoff = address % 4096;

        /*扇区剩余空间大小*/
        u16 secremain = 4096 - secoff;

        u16 i;

        u8 * W25QXX_BUF = W25QXX_BUFFER;

        if(length <= secremain)
        {
                secremain = length;
        }
        while(1)
        {
                /*读出整个扇区的内容*/
                W25QXX_Read(W25QXX_BUF, secpos * 4096, 4096);

                /*校验本扇区要写入的空间*/
                for(i = 0; i < secremain; i++)
                {
                        /*只要其中有一块空间中的值不是0xff*/
                        if(W25QXX_BUF[secoff + i] != 0xff)
                                break;
                }

                /*如果上述for循环是通过break退出的，那么i就会小于secremain*/
                if(i < secremain)
                {
                        /*直接擦除整个扇区*/
                        W25QXX_EraseSector(secpos);
                        /*写入要写入的数据*/
                        for(i = 0; i < secremain; i++)
                        {
                                W25QXX_BUF[secoff + i] = pBuffer[i];
                        }
                        W25QXX_WriteNoCheck(W25QXX_BUF, secpos * 4096, 4096);

                }
                else
                {
                        W25QXX_WriteNoCheck(pBuffer, address, secremain);
                }

                if(length == secremain)
                {
                        break;
                }
                else
                {
                        secpos++;
                        secoff = 0;
                        pBuffer += secremain;
                        address += secremain;
                        length -= secremain;
                        if(length > 4096)
                                secremain = 4096;
                        else
                                secremain = length;
                }
        };
}

/**
 * @Description 擦除整个芯片
 */
void W25QXX_EraseChip(void)
{
        W25QXX_WriteEnable();
        W25QXX_WaitBusy();
        W25QXX_CS = 0;
        Spi_ReadWriteByte(W25X_ChipErase);
        W25QXX_CS = 1;
        W25QXX_WaitBusy();
}

/**
 * @Description 擦除一个扇区
 * @param Dst_Addr 扇区地址 根据实际容量设置
 * @note 擦除一个扇区的最少时间150ms
 */
void W25QXX_EraseSector(u32 Dst_Addr)
{
        Dst_Addr *= 4096;
        W25QXX_WriteEnable();
        W25QXX_WaitBusy();
        W25QXX_CS = 0;
        Spi_ReadWriteByte(W25X_SectorErase);
        Spi_ReadWriteByte((u8)((Dst_Addr) >> 16));
        Spi_ReadWriteByte((u8)((Dst_Addr) >> 8));
        Spi_ReadWriteByte((u8) Dst_Addr);
        W25QXX_CS = 1;
        W25QXX_WaitBusy();
}

/**
 * @Description 等待空闲
 */
void W25QXX_WaitBusy(void)
{
        /* 等待BUSY位清空 */
        while((W25QXX_ReadSR() & 0x01) == 0x01)
        {
        }
}

/**
 * @Description 进入掉电模式
 */
void W25QXX_PowerDown(void)
{
        W25QXX_CS = 0;
        Spi_ReadWriteByte(W25X_PowerDown);
        W25QXX_CS = 1;
        delay_us(3);
}

/**
 * @Description 进入唤醒模式
 */
void W25QXX_WakeUp(void)
{
        W25QXX_CS = 0;
        Spi_ReadWriteByte(W25X_ReleasePowerDown);
        W25QXX_CS = 1;
        delay_us(3);
}

