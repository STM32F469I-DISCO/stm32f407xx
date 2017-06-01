#include "stm32f4xx.h"
#include "explore_system.h"
#include "explore_systick.h"
#include "explore_usart.h"
#include "driver_led.h"
#include "driver_exti.h"
#include "driver_iwdg.h"

int main(void)
{
	/*串口计数变量*/
	u8 i = 0;

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	Systick_Init(168);
	Usart_Init(115200);
	LED_Init();
	Exti_Init();
	Iwdg_Init(4, 500);

	/*延时1000ms后点亮LED0，如果没有持续喂狗，则点亮之后又会复位*/
	/*复位就意味着LED0会灭1s后再亮，也就是会闪烁*/
	delay_ms(100);
	LED0 = LED_ON;

	while (1)
	{
		/*如果持续喂狗，则会停在这个循环中，可以通过观察串口判断是否发生复位动作*/
		printf("running time is %d \r\n", i++);
		delay_ms(100);
	}
}
