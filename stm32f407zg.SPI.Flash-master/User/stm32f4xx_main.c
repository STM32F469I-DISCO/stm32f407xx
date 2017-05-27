#include "stm32f4xx.h"
#include "bsp_systick.h"
#include "bsp_usart.h"
#include "bsp_led.h"
#include "bsp_lcd.h"
#include "bsp_key.h"
#include "bsp_spi.h"
#include "bsp_w25qxx.h"

/* 要写入到W25Q16的字符串数组 */
const u8 TEXT_Buffer[] = { "Explorer STM32F4 Spi Test" };

/* 定义一个宏，保存字符串数组的大小 */
#define SIZE sizeof(TEXT_Buffer)

int main(void)
{
	u8 KeyValue;
	u16 i = 0;
	u8 TempData[SIZE];
	u32 FLASH_SIZE;

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	Systick_Init();
	Usart_Init();
	Led_Init();
	Lcd_Init();
	Key_Init();
	W25QXX_Init();

	POINT_COLOR = RED;
	BACK_COLOR = WHITE;
	Lcd_ClearScreen(BACK_COLOR);
	Lcd_CenterShowString(50, "Spi Flash Project", 24);

	POINT_COLOR = BLUE;

	/* 检测不到W25Q128 */
	while(W25QXX_ReadID() != W25Q128)
	{
		Lcd_Fill(0, 100, 480, 190, WHITE);
		Lcd_ShowString(30, 100, 400, 30, 24, "W25Q128 Check Failed!");
		delay_ms(500);
		Lcd_ShowString(30, 130, 400, 30, 24, "Please Check!        ");
		delay_ms(500);
		LED0 = !LED0;
	}

	Lcd_Fill(0, 100, 480, 190, BACK_COLOR);
	Lcd_ShowString(30, 100, 420, 30, 24, "W25Q128 Ready!");
	POINT_COLOR = RED;
	Lcd_ShowString(30, lcddev.height - 80, 420, 30, 24, "Key1: Write data to flash!");
	Lcd_ShowString(30, lcddev.height - 50, 420, 30, 24, "Key0: Read data from flash!");
	POINT_COLOR = BLUE;

	FLASH_SIZE = 16 * 1024 * 1024;
	POINT_COLOR = BLUE;
        
	while(1)
	{
                
		KeyValue = Key_Scan();
		if(KeyValue == KEY1_PRESS)
		{
			Lcd_Fill(0, 100, 480, 190, WHITE);
			Lcd_ShowString(30, 100, 420, 30, 24, "W25Q128 Ready!");
			Lcd_ShowString(30, 130, 420, 30, 24, "Start Write W25Q128....");
			W25QXX_Write((u8*) TEXT_Buffer, FLASH_SIZE - 100, SIZE);
			Lcd_ShowString(30, 160, 420, 30, 24, "W25Q128 Write Finished!");
		}
		if(KeyValue == KEY0_PRESS)
		{
			Lcd_Fill(0, 100, 480, 190, WHITE);
			Lcd_ShowString(30, 100, 420, 30, 24, "W25Q128 Ready!");
			Lcd_ShowString(30, 130, 420, 30, 24, "Start Read W25Q128.... ");
			W25QXX_Read(TempData, FLASH_SIZE - 100, SIZE);
			Lcd_ShowString(30, 130, 420, 30, 24, "The Data Readed Is:   ");
			Lcd_ShowString(30, 160, 420, 30, 24, (char *) TempData);
		}
		i++;
		delay_ms(10);
		if(i == 20)
		{
			LED0 = !LED0;
			i = 0;
		}
	}
}
