#include "stm32f4xx.h"
#include "explore_system.h"
#include "explore_systick.h"
#include "explore_usart.h"
#include "driver_led.h"
#include "driver_lcd.h"
#include "driver_dht11.h"
#include "string.h"

extern u8 DHT11_StatusCode;
extern u8 DHT11_Data[5];

int main(void)
{
	char str1[] = "humdity = ";
	char str2[] = "temperature = ";
	u8 len1 = strlen(str1);
	u8 len2 = strlen(str2);

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	Systick_Init(168);
	Usart_Init(115200);
	LED_Init();
	LCD_Init();
	DHT_Init();

	POINT_COLOR = RED;
	BACK_COLOR = WHITE;
	LCD_CenterShowString(50, "Temperature Experiment", 24);
	POINT_COLOR = BLUE;

	while(1)
	{
		/*读取一次温湿度信息*/
		DHT_ReadData();

		/*根据返回的"DHT11_StatusCode"值完成指定的操作*/
		switch(DHT11_StatusCode)
		{
		case 0:
			printf("humdity = %d.0 %% temperature = %d.0 C\r\n", DHT11_Data[0], DHT11_Data[2]);

			LCD_Fill(0, 100, 480, 160, BACK_COLOR);
			LCD_ShowString(30, 100, len1 * 12, 30, 24, str1);
			LCD_ShowInt(30 + len1 * 12, 100, DHT11_Data[0], 24);
			LCD_ShowString(30 + (len1 + 2) * 12, 100, 12, 30, 24, "%");

			LCD_ShowString(30, 130, len2 * 12, 30, 24, str2);
			LCD_ShowInt(30 + len2 * 12, 130, DHT11_Data[2], 24);
			LCD_ShowString(30 + (len2 + 2) * 12, 130, 12, 30, 24, "C");
			break;
		case 1:
			LCD_Fill(0, 100, 480, 160, BACK_COLOR);
			LCD_ShowString(30, 100, 420, 30, 24, "Error 1: DHT start condition 1 not met.");
			printf("Error 1: DHT start condition 1 not met.\n");
			break;
		case 2:
			LCD_Fill(0, 100, 480, 160, BACK_COLOR);
			LCD_ShowString(30, 100, 420, 30, 24, "Error 2: DHT start condition 2 not met.");
			printf("Error 2: DHT start condition 2 not met.\n");
			break;
		case 3:
			LCD_Fill(0, 100, 480, 160, BACK_COLOR);
			LCD_ShowString(30, 100, 420, 30, 24, "Error 3: DHT checksum error.");
			printf("Error 3: DHT checksum error.\n");
			break;
		default:
			LCD_Fill(0, 100, 480, 160, BACK_COLOR);
			LCD_ShowString(30, 100, 420, 30, 24, "Error: Unrecognized code encountered.");
			printf("Error: Unrecognized code encountered.\n");
			break;
		}
		delay_ms(1000);
	}
}
