#include "stm32f4xx.h"
#include "explore_system.h"
#include "explore_systick.h"
#include "explore_usart.h"
#include "driver_led.h"

/*for循环计数变量*/
u8 t;
/*保存接收数据的长度*/
u8 len;
/*一个用于计时的变量*/
u16 times = 0;

int main(void)
{
	/*本工程使用了串口中断，因此中断要分组*/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	Systick_Init(168);
	Usart_Init(115200);
	LED_Init();

	while (1)
	{
		/*如果接收完了所有的字符(每一次串口中断接收一个字符)*/
		if (USART_RX_STA & 0x8000)
		{
			/*得到此次接收到的数据长度*/
			len = USART_RX_STA & 0x3fff;
			printf("Your input is: ");
			/*将接收的数据原封不动的打印回上位机*/
			for (t = 0; t < len; t++)
			{
				/*向串口1发送数据，依次发送接收到的每一个字符*/
				USART_SendData(USART1, USART_RX_BUF[t]);
				/*等待发送结束*/
				while (USART_GetFlagStatus(USART1, USART_FLAG_TC) != SET)
					;
			}
			/*插入换行*/
			printf("\r\n");
			/*全部发送完成之后，清空自定义的标志寄存器*/
			USART_RX_STA = 0;
		}
		else
		{
			/*在数据没有接收到或者没有接收完的情况下*/
			times++;
			if (times % 200 == 0)
			{
				/*每隔200*10ms = 2000ms 打印提示语句*/
				printf("I can output your input.\r\n");
			}
			if (times % 30 == 0)
			{
				/*每隔30*10 = 300ms 闪烁LED,提示系统正在运行*/
				DS0 = !DS0;
			}
			/*每隔10ms检查一次*/
			delay_ms(10);
		}
	}
}
