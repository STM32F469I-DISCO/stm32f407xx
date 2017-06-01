#include "stm32f4xx.h"
#include "explore_system.h"
#include "explore_systick.h"
#include "explore_usart.h"
#include "driver_led.h"
#include "driver_lcd.h"
#include "driver_sram.h"
#include "string.h"

/*__attribute__,这个是用来指定变量或结构位域的特殊属性,该关键字后的双括弧中的内容是属性说明*/
/*at,该关键字可以用来设置变量的绝对地址,通过这个关键字,指定某个变量处于内存里面的某个给定的地址*/
/*可以通过Debug查看内存中的值*/
u16 testsram[25000] __attribute__((at(0X68000000)));

int main(void)
{
	/*循环使用到的变量*/
	u32 i = 0;

	/*用于读取和写入缓冲的数组*/
	u8 temp[20];

	/*初始化使用到的资源*/
	Systick_Init(168);
	Usart_Init(115200);
	LED_Init();
	LCD_Init();
	Sram_Init();

	/*先绘制实验的标题*/
	POINT_COLOR = RED;
	BACK_COLOR = WHITE;
	LCD_CenterShowString(50, "SRAM Experiment", 24);

	POINT_COLOR = BLUE;

	/*在SRAM中先存入250000个半字，为什么是半字，因为testsram数组是u16类型*/
	/*1M内存可以存2^20个字节，可以存2^19=524288个半字*/
	for(i = 0; i < 250000; i++)
		testsram[i] = i;

	LCD_ShowString(20, 100, 400, 30, 24, "The stored data:");

	/*从地址0的位置读取10个数，显示在屏幕上*/
	/*同时观察debug内存数据值，验证读取函数*/
	Sram_ReadBuffer(temp, 0, 10);
	for(i = 0; i < 10; i++)
	{
		LCD_ShowInt(20 + 45 * i, 130, temp[i], 24);
	}

	/*给temp数组重新赋值，写入SRAM，观察Debug内存数据，验证写入函数*/
	for(i = 0; i < 10; i++)
	{
		temp[i] = 100 + i;
	}
	Sram_WriteBuffer(temp, 0, 10);

	LCD_ShowString(20, 160, 400, 30, 24, "The new value:");

	/*从地址0的位置读取10个数，显示在屏幕上，此时显示的是新值*/
	Sram_ReadBuffer(temp, 0, 10);
	for(i = 0; i < 10; i++)
	{
		LCD_ShowInt(20 + 45 * i, 190, temp[i], 24);
	}

	/*指示灯标记程序正在运行*/
	LED0 = LED_ON;
	while(1)
	{
		LED0 = ~LED0;
		delay_ms(500);
	}
}
