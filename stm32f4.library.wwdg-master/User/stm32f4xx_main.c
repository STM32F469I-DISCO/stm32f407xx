#include "stm32f4xx.h"
#include "explore_system.h"
#include "explore_systick.h"
#include "explore_usart.h"
#include "driver_led.h"
#include "driver_wwdg.h"

/**
 * @Description 主函数
 */
int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	Systick_Init(168);
	Usart_Init(115200);
	LED_Init();

	/*DS0亮一秒之后再也不亮*/
	LED0 = LED_ON;
	delay_ms(1000);

	/*初始化看门狗*/
	Wwdg_Init(WWDG_Prescaler_8, 0x5F);

	while (1)
	{
		DS0 = LED_OFF;
	}
}
