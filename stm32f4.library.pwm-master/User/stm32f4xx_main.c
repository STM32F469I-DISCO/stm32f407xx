#include "stm32f4xx.h"
#include "explore_system.h"
#include "explore_systick.h"
#include "explore_usart.h"
#include "driver_led.h"
#include "driver_timer.h"

#define ADD 1
#define SUB 0

int main(void)
{
	u16 pwm_value = 0;
	u8 flag = ADD;
	u8 sikp = 5;

	Systick_Init(168);
	Usart_Init(115200);
	LED_Init();

	/*84M/84=1Mhz的计数频率,重装载值500，所以PWM频率为 1M/500=2Khz.*/
	TIM14_Init(500, 84);
	
	while (1)
	{
		delay_ms(10);
		if (flag)
		{
			/*dir==1 led0 pwmval递增*/
			pwm_value = pwm_value + sikp;
			if (pwm_value > 500)
				flag = SUB;
		}
		else
		{
			/*dir==0 led0 pwmval递减*/
			pwm_value = pwm_value - sikp;
			if (pwm_value <= 0)
				flag = ADD;
		}

		/*修改比较值，修改占空比*/
		TIM_SetCompare1(TIM14, pwm_value);
	}
}
