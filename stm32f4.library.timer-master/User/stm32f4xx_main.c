#include "stm32f4xx.h"
#include "explore_system.h"
#include "explore_systick.h"
#include "explore_usart.h"
#include "driver_led.h"
#include "driver_timer.h"

int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	Systick_Init(168);
	Usart_Init(115200);
	LED_Init();

	/*定时器时钟84M，分频系数8400，所以84M/8400=10Khz的计数频率，计数5000次为500ms*/
	TIM3_Init(5000, 8400);
	while (1)
	{
		/*DS0翻转*/
		DS0 = !DS0;

		/*延时500ms*/
		delay_ms(500);

		/*利用串口时间戳观察时间间隔*/
		printf("DS0 -------------------------   \r\n");
	}
}

