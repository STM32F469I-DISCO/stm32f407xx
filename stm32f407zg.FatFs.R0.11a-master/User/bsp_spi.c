#include "bsp_spi.h"

/* 驱动版本号：bsp_spi v1.3 */

/**
 * @Description SPI初始化
 */
void Spi_Init(void)
{
        GPIO_InitTypeDef GPIO_InitStructure;
        SPI_InitTypeDef SPI_InitStructure;

        /* 第一步：使能SPI对应GPIO以及SPI时钟 */
        SPI_APBxPeriphClockCmd(RCC_APBxPeriph_SPIx, ENABLE);
        RCC_AHB1PeriphClockCmd(SPI_MOSI_GPIO_CLK, ENABLE);
        RCC_AHB1PeriphClockCmd(SPI_MISO_GPIO_CLK, ENABLE);
        RCC_AHB1PeriphClockCmd(SPI_SCK_GPIO_CLK, ENABLE);

        /* 第二步：配置SPI引脚为复用推挽输出 */
        GPIO_InitStructure.GPIO_Pin = SPI_MOSI_PIN;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
        GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
        GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
        GPIO_Init(SPI_MOSI_GPIO_PORT, &GPIO_InitStructure);

        GPIO_InitStructure.GPIO_Pin = SPI_MISO_PIN;
        GPIO_Init(SPI_MISO_GPIO_PORT, &GPIO_InitStructure);

        GPIO_InitStructure.GPIO_Pin = SPI_SCK_PIN;
        GPIO_Init(SPI_SCK_GPIO_PORT, &GPIO_InitStructure);

        /* 第三步：配置SPI引脚复用映射 */
        GPIO_PinAFConfig(SPI_MOSI_GPIO_PORT, SPI_MOSI_SOURCE, SPI_MOSI_AF);
        GPIO_PinAFConfig(SPI_MISO_GPIO_PORT, SPI_MISO_SOURCE, SPI_MISO_AF);
        GPIO_PinAFConfig(SPI_SCK_GPIO_PORT, SPI_SCK_SOURCE, SPI_SCK_AF);

        /* 第四步：针对SPI口初始化 */
        SPI_APBxPeriphResetCmd(RCC_APBxPeriph_SPIx, ENABLE);            // 复位SPI
        SPI_APBxPeriphResetCmd(RCC_APBxPeriph_SPIx, DISABLE);           // 停止复位SPI

        /* 第五步：配置SPI传输模式 */
        /* 设置SPI单向或者双向的数据模式：SPI设置为双线双向全双工 */
        SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;

        /* 设置SPI工作模式：设置为主SPI */
        SPI_InitStructure.SPI_Mode = SPI_Mode_Master;

        /* 设置SPI的数据大小8位或者16位：SPI发送接收8位帧结构 */
        SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;

        /* 设置串行同步时钟的空闲状态：空闲状态为高电平 */
        SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;

        /* 设置串行同步时钟的第二个跳变沿(上升或下降)数据被采样 */
        SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;

        /* NSS信号由硬件(NSS管脚)还是软件(使用SSI位)管理：内部NSS信号由SSI位(软件)控制 */
        SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;

        /* 定义波特率预分频的值：波特率预分频值为256 */
        SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;

        /* 指定数据传输从MSB位还是LSB位开始：数据传输从MSB位开始 */
        SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;

        /* CRC值计算的多项式 */
        SPI_InitStructure.SPI_CRCPolynomial = 7;

        /* 根据SPI_InitStruct中指定的参数初始化外设SPIx寄存器 */
        SPI_Init(SPIx, &SPI_InitStructure);

        /* 第六步：使能SPI */
        SPI_Cmd(SPIx, ENABLE);

        /* 第七步：主机开始传输一个数据标志开始传输 */
        Spi_ReadWriteByte(0xff);
}

/**
 * @Description SPI速度设置函数
 * @param SpeedSet 分频数
 * @notice APB2时钟一般为84Mhz
 */
void Spi_SetSpeed(u8 SpeedSet)
{
        /* 判断有效性 */
        assert_param(IS_SPI_BAUDRATE_PRESCALER(SpeedSet));

        /* 位3-5清零，用来设置波特率 */
        SPIx->CR1 &= 0xffc7;

        /* 设置SPI速度 */
        SPIx->CR1 |= SpeedSet;

        /* 使能SPI */
        SPI_Cmd(SPIx, ENABLE);
}

/**
 * @Description 读写一个字节
 * @param data  要写入的字节
 * @return u8   读取到的字节
 */
u8 Spi_ReadWriteByte(u8 data)
{
        while(SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_TXE) == RESET)
        {
        }
        SPI_I2S_SendData(SPIx, data);

        while(SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_RXNE) == RESET)
        {
        }
        return SPI_I2S_ReceiveData(SPIx);
}

