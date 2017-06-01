#include "stm32f4xx.h"
#include "explore_system.h"
#include "explore_systick.h"
#include "explore_usart.h"
#include "driver_led.h"
#include "driver_lcd.h"
#include "driver_ultrasonic.h"

extern u8 TIM5CH1_CAPTURE_STA;						// 输入捕获状态
extern u32 TIM5CH1_CAPTURE_VAL;						// 输入捕获值

int main(void)
{
	long long temp = 0;						// 记录计数总数
	float m = 0.0;
	char *str;

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	Systick_Init(168);
	Usart_Init(115200);
	LED_Init();
	LCD_Init();
	Ultrasonic_Init(0xFFFFFFFF, 84 - 1);				// 以1Mhz的频率计数

	POINT_COLOR = RED;
	BACK_COLOR = WHITE;
	LCD_CenterShowString(50, "Ultrasonic Experiment", 24);

	POINT_COLOR = BLUE;

	while(1)
	{
		Ultrasonic_StartMeasure();				// 开始测量
		delay_ms(1000);

		if(TIM5CH1_CAPTURE_STA & 0X80)				// 成功捕获到了一次高电平
		{
			temp = TIM5CH1_CAPTURE_STA & 0X3F;		// 将定时器在高电平维持时间内溢出的次数取出来
			temp *= 0XFFFFFFFF;				// 溢出时间总和
			temp += TIM5CH1_CAPTURE_VAL;			// 得到总的高电平时间
			m = temp * 340.0 / 1000000.0 / 2;
			sprintf(str, "%2.3f", m);
			printf("m = %2.3f\r\n", m);
			TIM5CH1_CAPTURE_STA = 0;			// 开启下一次捕获
		}
	}
}
