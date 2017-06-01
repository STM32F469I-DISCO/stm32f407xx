#include "stm32f4xx.h"
#include "explore_system.h"
#include "explore_systick.h"
#include "explore_usart.h"
#include "driver_led.h"
#include "driver_lcd1602.h"

int main(void)
{
	Systick_Init(168);
	Usart_Init(115200);
	LED_Init();
	LCD1602_Init();
	LCD1602_WriteString(0, 0, "LCD1602_Demo");
	
	while(1)
	{
		
	}
}
