#include "stm32f4xx.h"
#include "explore_system.h"
#include "explore_systick.h"
#include "explore_usart.h"
#include "driver_led.h"
#include "driver_lcd.h"
#include "driver_random.h"

int main(void)
{
	u32 random;

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	Systick_Init(168);
	Usart_Init(115200);
	LED_Init();
	LCD_Init();
	while (Random_Init());

	POINT_COLOR = RED;
	BACK_COLOR = WHITE;
	LCD_ClearScreen(BACK_COLOR);
	LCD_ShowString(140, 50, 440, 30, 24, "Random experiment");

	POINT_COLOR = BLUE;
	LCD_ShowString(20, 100, 440, 24, 24, "Random Num[0-15]:");

	while (1)
	{
		LED0 = !LED0;
		random = Random_GetRangeNumber(0, 15);
		LCD_Fill(20 + 12 * 18, 100, 480, 130, BACK_COLOR);
		LCD_ShowInt(20 + 12 * 18, 100, random, 24);
		delay_ms(500);
	}
}
