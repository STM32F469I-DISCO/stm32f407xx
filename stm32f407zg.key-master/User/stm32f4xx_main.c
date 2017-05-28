#include "stm32f4xx.h"
#include "bsp_systick.h"
#include "bsp_usart.h"
#include "bsp_led.h"
#include "bsp_lcd.h"
#include "bsp_beep.h"
#include "bsp_key.h"

int main(void)
{
        u8 key;
        
        NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
        Systick_Init();
        Usart_Init();
        Led_Init();
        Lcd_Init();
        Key_Init();
        Beep_Init();

        POINT_COLOR = BLUE;
        BACK_COLOR = WHITE;
        Lcd_CenterShowString(50, "Key Project", 24);

        while(1)
        {
                key = Key_Scan();
		if (key)
		{
			switch (key)
			{
			case WKUP_PRESS:
				BEEP = !BEEP;
				break;
			case KEY0_PRESS:
				LED0 = !LED0;
				break;
			case KEY1_PRESS:
				LED1 = !LED1;
				break;
			case KEY2_PRESS:
				LED0 = !LED0;
				LED1 = !LED1;
				break;
			}
		}
		else
		{
			delay_ms(10);
		}
        }
}
