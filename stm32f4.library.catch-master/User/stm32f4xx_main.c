#include "stm32f4xx.h"
#include "explore_system.h"
#include "explore_systick.h"
#include "explore_usart.h"
#include "driver_led.h"
#include "driver_timer.h"
#include "driver_lcd.h"

/*输入捕获状态*/
extern u8 TIM5CH1_CAPTURE_STA;
/*输入捕获值*/
extern u32 TIM5CH1_CAPTURE_VAL;

int main(void)
{
	/*记录计数总数*/
	long long temp = 0;

	/*格式转化用到的数据 秒*/
	u32 s = 0;

	/*格式转化用到的数据 毫秒*/
	u16 ms = 0;

	/*格式转化用到的数据 微秒*/
	u16 us = 0;

	u8 length;
	u16 location;

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	Systick_Init(168);
	Usart_Init(115200);
	LED_Init();
	LCD_Init();

	/*以1Mhz的频率计数*/
	TIM5_Init(0xFFFFFFFF, 84);

	POINT_COLOR = RED;
	BACK_COLOR = WHITE;
	LCD_ClearScreen(BACK_COLOR);
	LCD_ShowString(60, 50, 440, 30, 24, "The input capture experiment");

	while (1)
	{
		delay_ms(10);

		/*成功捕获到了一次高电平*/
		if (TIM5CH1_CAPTURE_STA & 0X80)
		{
			/*将定时器在高电平维持时间内溢出的次数取出来*/
			temp = TIM5CH1_CAPTURE_STA & 0X3F;

			/*溢出时间总和*/
			temp *= 0XFFFFFFFF;

			/*得到总的高电平时间*/
			temp += TIM5CH1_CAPTURE_VAL;

			/*除以1000000是因为定时器的时钟为1M*/
			s = temp / 1000000;
			ms = (temp % 1000000) / 1000;
			us = temp % 1000;

			/*打印总的高点平时间*/
			printf("High level last time: %lld us\r\n", temp);

			POINT_COLOR = BLUE;
			LCD_Fill(0, 100, 480, 124, BACK_COLOR);
			LCD_ShowString(20, 100, 440, 24, 24, "High level last time: ");
			length = LCD_ShowInt(284, 100, temp, 24);
			LCD_ShowString(284 + 12 * length, 100, 24, 30, 24, "us");

			/*打印总的高点平时间*/
			printf("%d s %d ms %d us\r\n", s, ms, us);

			LCD_Fill(0, 130, 480, 154, BACK_COLOR);
			LCD_ShowString(20, 130, 440, 24, 24, "High level last time: ");
			location = 284;

			length = LCD_ShowInt(location, 130, s, 24);
			location = location + 12 * length;
			LCD_ShowString(location, 130, 24, 30, 24, "s");
			location = location + 24;

			length = LCD_ShowInt(location, 130, ms, 24);
			location = location + 12 * length;
			LCD_ShowString(location, 130, 24, 30, 24, "ms");
			location = location + 36;

			length = LCD_ShowInt(location, 130, us, 24);
			location = location + 12 * length;
			LCD_ShowString(location, 130, 24, 30, 24, "us");

			/*开启下一次捕获*/
			TIM5CH1_CAPTURE_STA = 0;
		}
	}
}
