#include "driver_lcd1602.h"

/**
 * @Description LCD1602 数据/命令选择
 * @param bit 0：命令模式 1：数据模式
 */
void LCD1602_RS(u8 bit)
{
	GPIO_WriteBit(RS_GPIO_PORT, RS_GPIO_PIN, (BitAction)bit);
}

/**
 * @Description LCD1602 读/写选择
 * @param bit 0：写操作 1：读操作
 */
void LCD1602_RW(u8 bit)
{
	GPIO_WriteBit(RW_GPIO_PORT, RW_GPIO_PIN, (BitAction)bit);
}

/**
 * @Description LCD1602 使能位
 * @param bit 0：未使能 1：使能
 */
void LCD1602_E(u8 bit)
{
	GPIO_WriteBit(E_GPIO_PORT, E_GPIO_PIN, (BitAction)bit);
}

/**
 * @Description LCD1602 写命令
 * @param cmd 8位命令值
 */
void LCD1602_WriteCmd(u8 cmd)
{
	LCD1602_E(0);
	LCD1602_RS(0);
	LCD1602_RW(0);
	GPIO_WriteBit(DATA0_GPIO_PORT, DATA0_GPIO_PIN, (BitAction)((cmd>>0)&0x01));
	GPIO_WriteBit(DATA1_GPIO_PORT, DATA1_GPIO_PIN, (BitAction)((cmd>>1)&0x01));
	GPIO_WriteBit(DATA2_GPIO_PORT, DATA2_GPIO_PIN, (BitAction)((cmd>>2)&0x01));
	GPIO_WriteBit(DATA3_GPIO_PORT, DATA3_GPIO_PIN, (BitAction)((cmd>>3)&0x01));
	GPIO_WriteBit(DATA4_GPIO_PORT, DATA4_GPIO_PIN, (BitAction)((cmd>>4)&0x01));
	GPIO_WriteBit(DATA5_GPIO_PORT, DATA5_GPIO_PIN, (BitAction)((cmd>>5)&0x01));
	GPIO_WriteBit(DATA6_GPIO_PORT, DATA6_GPIO_PIN, (BitAction)((cmd>>6)&0x01));
	GPIO_WriteBit(DATA7_GPIO_PORT, DATA7_GPIO_PIN, (BitAction)((cmd>>7)&0x01));
	LCD1602_E(1);
	delay_ms(1);
	LCD1602_E(0);
}

/**
 * @Description LCD1602 写数据
 * @param dat 8位数据值
 */
void LCD1602_WriteDat(u8 dat)
{
	LCD1602_E(0);
	LCD1602_RS(1);
	LCD1602_RW(0);
	GPIO_WriteBit(DATA0_GPIO_PORT, DATA0_GPIO_PIN, (BitAction)((dat>>0)&0x01));
	GPIO_WriteBit(DATA1_GPIO_PORT, DATA1_GPIO_PIN, (BitAction)((dat>>1)&0x01));
	GPIO_WriteBit(DATA2_GPIO_PORT, DATA2_GPIO_PIN, (BitAction)((dat>>2)&0x01));
	GPIO_WriteBit(DATA3_GPIO_PORT, DATA3_GPIO_PIN, (BitAction)((dat>>3)&0x01));
	GPIO_WriteBit(DATA4_GPIO_PORT, DATA4_GPIO_PIN, (BitAction)((dat>>4)&0x01));
	GPIO_WriteBit(DATA5_GPIO_PORT, DATA5_GPIO_PIN, (BitAction)((dat>>5)&0x01));
	GPIO_WriteBit(DATA6_GPIO_PORT, DATA6_GPIO_PIN, (BitAction)((dat>>6)&0x01));
	GPIO_WriteBit(DATA7_GPIO_PORT, DATA7_GPIO_PIN, (BitAction)((dat>>7)&0x01));
	LCD1602_E(1);
	delay_ms(1);
	LCD1602_E(0);
}

/**
 * @Description LCD1602 初始化函数
 */
void LCD1602_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RS_GPIO_CLK, ENABLE);
	RCC_AHB1PeriphClockCmd(RW_GPIO_CLK, ENABLE);
	RCC_AHB1PeriphClockCmd(E_GPIO_CLK, ENABLE);
	RCC_AHB1PeriphClockCmd(DATA0_GPIO_CLK, ENABLE);
	RCC_AHB1PeriphClockCmd(DATA1_GPIO_CLK, ENABLE);
	RCC_AHB1PeriphClockCmd(DATA2_GPIO_CLK, ENABLE);
	RCC_AHB1PeriphClockCmd(DATA3_GPIO_CLK, ENABLE);
	RCC_AHB1PeriphClockCmd(DATA4_GPIO_CLK, ENABLE);
	RCC_AHB1PeriphClockCmd(DATA5_GPIO_CLK, ENABLE);
	RCC_AHB1PeriphClockCmd(DATA6_GPIO_CLK, ENABLE);
	RCC_AHB1PeriphClockCmd(DATA7_GPIO_CLK, ENABLE);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;

	GPIO_InitStructure.GPIO_Pin = RS_GPIO_PIN;
	GPIO_Init(RS_GPIO_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = RW_GPIO_PIN;
	GPIO_Init(RW_GPIO_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = E_GPIO_PIN;
	GPIO_Init(E_GPIO_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = DATA0_GPIO_PIN;
	GPIO_Init(DATA0_GPIO_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = DATA1_GPIO_PIN;
	GPIO_Init(DATA1_GPIO_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = DATA2_GPIO_PIN;
	GPIO_Init(DATA2_GPIO_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = DATA3_GPIO_PIN;
	GPIO_Init(DATA3_GPIO_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = DATA4_GPIO_PIN;
	GPIO_Init(DATA4_GPIO_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = DATA5_GPIO_PIN;
	GPIO_Init(DATA5_GPIO_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = DATA6_GPIO_PIN;
	GPIO_Init(DATA6_GPIO_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = DATA7_GPIO_PIN;
	GPIO_Init(DATA7_GPIO_PORT, &GPIO_InitStructure);

	LCD1602_WriteCmd(0x38);
	LCD1602_WriteCmd(0x0c);
	LCD1602_WriteCmd(0x06);
	LCD1602_WriteCmd(0x01);
	LCD1602_WriteCmd(0x80);
}

/**
 * @Description LCD1602 显示字符串
 * @param x 行号，取值范围为0-1
 * @param x 列号，取值范围为0-15
 */
void LCD1602_WriteString(u8 x, u8 y, char* str)
{
	if(x == 0)
	{
		LCD1602_WriteCmd(0x80 | y);
	}
	else if(x == 1)
	{
		LCD1602_WriteCmd(0xc0 | y);
	}
	while(*str!='\0')
	{
		LCD1602_WriteDat(*str);
		str++;
	}
}
