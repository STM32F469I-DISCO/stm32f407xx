#include "driver_timer.h"

/**
 * @Description 初始化TIM3函数
 * @param arr 自动重装载值
 * @param psc 定时器分频系数
 * @return null	无返回值
 */
void TIM3_Init(u16 arr, u16 psc)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;

	/*第一步：使能定时器的时钟*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	/*第二步：配置定时器参数*/
	/*设置定时器自动重装载值*/
	TIM_TimeBaseInitStructure.TIM_Period = arr - 1;
	/*设置定时器分频系数*/
	TIM_TimeBaseInitStructure.TIM_Prescaler = psc - 1;
	/*设置定时器计数模式为向上计数模式*/
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	/*暂时未使用，不重要*/
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	/*初始化TIM3*/
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);

	/*第三步：开启定时器中断(定时器更新中断)*/
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);

	/*第四步：配置定时器中断*/
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	/*第五步：使能定时器*/
	TIM_Cmd(TIM3, ENABLE);
}

/**
 * Descrition 定时器3中断服务函数
 */
void TIM3_IRQHandler(void)
{
	/*判断是否是溢出中断*/
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) == SET)
	{
		/*每0.5秒 DS1翻转*/
		DS1 = !DS1;

		/*利用串口时间戳观察时间间隔*/
		printf("DS1 *************************   \r\n");
	}
	/*清除中断标志位*/
	TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
}
