#include "driver_sram.h"

/**
 * @Description 初始化外部SRAM
 */
void Sram_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	FSMC_NORSRAMInitTypeDef FSMC_NORSRAMInitStructure;
	FSMC_NORSRAMTimingInitTypeDef ReadWriteTiming;

	/*第一步：使能FSMC时钟和GPIO时钟*/
	RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FSMC, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);

	/*PB15 推挽输出，用于控制背光*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	/*下面配置的GPIO全部是FSMC复用的I/O*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;

	/*FSMC_A0 - PF0*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_Init(GPIOF, &GPIO_InitStructure);
	/*FSMC_A1 - PF1*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_Init(GPIOF, &GPIO_InitStructure);
	/*FSMC_A2 - PF2*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_Init(GPIOF, &GPIO_InitStructure);
	/*FSMC_A3 - PF3*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_Init(GPIOF, &GPIO_InitStructure);
	/*FSMC_A4 - PF4*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_Init(GPIOF, &GPIO_InitStructure);
	/*FSMC_A5 - PF5*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_Init(GPIOF, &GPIO_InitStructure);
	/*FSMC_A6 - PF12*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_Init(GPIOF, &GPIO_InitStructure);
	/*FSMC_A7 - PF13*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_Init(GPIOF, &GPIO_InitStructure);
	/*FSMC_A8 - PF14*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
	GPIO_Init(GPIOF, &GPIO_InitStructure);
	/*FSMC_A9 - PF15*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_Init(GPIOF, &GPIO_InitStructure);
	/*FSMC_A10 - PG0*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_Init(GPIOG, &GPIO_InitStructure);
	/*FSMC_A11 - PG1*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_Init(GPIOG, &GPIO_InitStructure);
	/*FSMC_A12 - PG2*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_Init(GPIOG, &GPIO_InitStructure);
	/*FSMC_A13 - PG3*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_Init(GPIOG, &GPIO_InitStructure);
	/*FSMC_A14 - PG4*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_Init(GPIOG, &GPIO_InitStructure);
	/*FSMC_A15 - PG5*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_Init(GPIOG, &GPIO_InitStructure);
	/*FSMC_A16 - PD11*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	/*FSMC_A17 - PD12*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	/*FSMC_A18 - PD13*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	/*FSMC_D0 - PD14*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	/*FSMC_D1 - PD15*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	/*FSMC_D2 - PD0*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	/*FSMC_D3 - PD1*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	/*FSMC_D4 - PE7*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	/*FSMC_D5 - PE8*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	/*FSMC_D6 - PE9*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	/*FSMC_D7 - PE10*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	/*FSMC_D8 - PE11*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	/*FSMC_D9 - PE12*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	/*FSMC_D10 - PE13*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	/*FSMC_D11 - PE14*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	/*FSMC_D12 - PE15*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	/*FSMC_D13 - PD8*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	/*FSMC_D14 - PD9*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	/*FSMC_D15 - PD10*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	/*FSMC_NOE - PD4*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	/*FSMC_NWE - PD5*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	/*FSMC_NBL0 - PG10*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_Init(GPIOG, &GPIO_InitStructure);
	/*FSMC_BLN1 - PE0*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	/*FSMC_NE3 - PE1*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	/*第二步：配置GPIO复用映射*/
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource0, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource1, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource4, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource5, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource8, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource9, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource10, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource11, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource12, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource13, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_FSMC);

	GPIO_PinAFConfig(GPIOE, GPIO_PinSource0, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource1, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource7, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource8, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource9, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource10, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource11, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource12, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource13, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource14, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource15, GPIO_AF_FSMC);

	GPIO_PinAFConfig(GPIOF, GPIO_PinSource0, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource1, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource2, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource3, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource4, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource5, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource12, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource13, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource14, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource15, GPIO_AF_FSMC);

	GPIO_PinAFConfig(GPIOG, GPIO_PinSource0, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOG, GPIO_PinSource1, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOG, GPIO_PinSource2, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOG, GPIO_PinSource3, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOG, GPIO_PinSource4, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOG, GPIO_PinSource5, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOG, GPIO_PinSource10, GPIO_AF_FSMC);

	/*第三步：读写时序参数设置*/
	/*这些位定义地址的建立时间，适用于SRAM、ROM和异步总线复用模式的 NOR闪存操作*/
	/*地址建立时间(ADDSET)为1个HCLK 1/36M = 27ns*/
	ReadWriteTiming.FSMC_AddressSetupTime = 0x00;
	/*这些位定义地址的保持时间，适用于SRAM、ROM和异步总线复用模式的 NOR闪存操作*/
	/*地址保持时间(ADDHLD)模式A未用到，这里设置为0*/
	ReadWriteTiming.FSMC_AddressHoldTime = 0x00;
	/*这些位定义数据的保持时间，适用于SRAM、ROM和异步总线复用模式的NOR闪存操作*/
	/*这里设置数据保持时间(DATAST)为9个HCLK 6*9 = 54ns*/
	ReadWriteTiming.FSMC_DataSetupTime = 0x08;
	/*这些位用于定义一次读操作之后在总线上的延迟(仅适用于总线复用模式的NOR闪存操作)*/
	/*一次读操作之后控制器需要在数据总线上为下次操作送出地址，这个延迟就是为了防止总线冲突*/
	/*如果扩展的存储器系统不包含总线复用模式的存储器，或最慢的存储器可以在6个HCLK时钟周期内将数据总线恢复到高阻状态*/
	/*可以设置这个参数为其最小值*/
	ReadWriteTiming.FSMC_BusTurnAroundDuration = 0x00;
	/*定义CLK时钟输出信号的周期，以HCLK周期数表示*/
	ReadWriteTiming.FSMC_CLKDivision = 0x00;
	/*处于同步成组模式的NOR闪存，需要定义在读取第一个数据之前等待的存储器周期数目*/
	/*这个时间参数不是以HCLK表示，而是以闪存时钟(CLK)表示*/
	/*在访问异步NOR闪存、SRAM或ROM时，这个参数不起作用。操作C；RAM时，这个参数必须为0*/
	/*这里由于是操作SRAM，因此这个参数不起作用*/
	ReadWriteTiming.FSMC_DataLatency = 0x00;
	/*访问模式，这里设置位模式A*/
	ReadWriteTiming.FSMC_AccessMode = FSMC_AccessMode_A;

	/*第四步：FSMC配置*/
	/*NORSRAM被分为四块，其中这个参数是说明对那个块编程*/
	FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM3;
	/*地址/数据是否复用，这里设置不复用*/
	FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;
	/*存储器类型，这里设置为SRAM*/
	FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_SRAM;
	/*数据总线宽度8位/16位，这里设置为16位*/
	FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;
	/*是否进行成组模式访问，这里设置不进行成组访问模式*/
	FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;
	/*等待信号有效级性，这里设置为低电平有效*/
	FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
	/*启用或禁用异步传输信号等，仅异步Flash有效，这里设置禁用*/
	FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait = FSMC_AsynchronousWait_Disable;
	/*该位决定控制器是否支持把非对齐的AHB成组操作分割成2次线性操作，该位仅在存储器的成组模式下有效*/
	FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;
	/*当闪存存储器处于成组传输模式时，NWAIT信号指示从闪存存储器出来的数据是否有效或是否需要插入等待周期*/
	/*决定存储器是在等待状态之前的一个时钟周期产生NWAIT信号，还是在等待状态期间产生NWAIT信号*/
	FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
	/*指示FSMC是否允许/禁止对存储器的写操作*/
	FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
	/*当闪存存储器处于成组传输模式时，这一位允许/禁止通过NWAIT信号插入等待状态*/
	FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
	/*允许FSMC使用FSMC_BWTR寄存器，即允许读和写使用不同的时序，这里设置为不允许*/
	FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable;
	/*对于处于成组传输模式的闪存存储器，这一位允许/禁止通过NWAIT信号插入等待状态。读操作的同步成组传输协议使能位是FSMC_BCRx寄存器的BURSTEN位*/
	FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;
	/*读时序配置指针，这里使用上面配置的时序*/
	FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &ReadWriteTiming;
	/*写时序配置指针，这里也使用上面配置的时序，读写同一个时序*/
	FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &ReadWriteTiming;
	FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);

	/*第五步：使能BANK1区域3*/
	FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM3, ENABLE);
}

/**
 * @Description 在指定地址开始，连续写入n个字节
 * @param pBuffer 存放写入数据的缓冲区指针
 * @param WriteAddr 要写入的内存的地址(偏移地址)
 * @param num 要写入的字节数
 * @note 指定地址是指 WriteAddr+Bank1_SRAM3_ADDR
 */
void Sram_WriteBuffer(u8* pBuffer, u32 WriteAddr, u32 num)
{
	for(; num != 0; num--)
	{
		*(vu8*) (Bank1_SRAM3_ADDR + WriteAddr) = *pBuffer;
		WriteAddr++;
		pBuffer++;
	}
}

/**
 * @Description 在指定地址开始，连续读取n个字节
 * @param pBuffer 存放读出数据的缓冲区指针
 * @param WriteAddr 要读取的内存的的地址(偏移地址)
 * @param num 要读出的字节数
 * @note 指定地址是指 ReadAddr+Bank1_SRAM3_ADDR
 */
void Sram_ReadBuffer(u8* pBuffer, u32 ReadAddr, u32 n)
{
	for(; n != 0; n--)
	{
		*pBuffer++ = *(vu8*) (Bank1_SRAM3_ADDR + ReadAddr);
		ReadAddr++;
	}
}
