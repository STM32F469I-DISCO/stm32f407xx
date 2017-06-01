#include "stm32f4xx.h"
#include "explore_system.h"
#include "explore_systick.h"
#include "explore_usart.h"
#include "driver_led.h"
#include "driver_lcd.h"
#include "driver_adc.h"

int main(void)
{
	u16 adcx;
	float temp;
	u8 length;

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	Systick_Init(168);
	Usart_Init(115200);
	LED_Init();
	LCD_Init();
	Adc_Init();

	POINT_COLOR = RED;
	BACK_COLOR = WHITE;
	LCD_ClearScreen(BACK_COLOR);

	LCD_ShowString(60, 50, 440, 30, 24, "The ADC acquisition experiment");

	POINT_COLOR = BLUE;
	LCD_ShowString(30, 100, 450, 30, 24, "ADC2_CH6_VAL:");
	LCD_ShowString(30, 130, 450, 30, 24, "ADC2_CH6_VOL:");

	while (1)
	{
		/*获取通道6的转换值，21次取平均*/
		adcx = Adc_GetAverageValue(ADC_Channel_6, 21);

		/*显示ADC采样后的原始值*/
		LCD_Fill(186, 100, 480, 130, BACK_COLOR);
		LCD_ShowInt(198, 100, adcx, 24);

		/*获取计算后的带小数的实际电压值*/
		temp = (float) adcx * (3.3 / 4096);

		/*显示转化后的电压值*/
		LCD_Fill(186, 130, 480, 160, BACK_COLOR);
		length = LCD_ShowFloat(198, 130, temp, 24);
		LCD_ShowChar(198 + length * 12, 130, 'V', 24, DRAW_DIRECT);

		LED0 = !LED0;

		delay_ms(250);
	}
}
