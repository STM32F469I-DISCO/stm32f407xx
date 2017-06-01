#include "driver_ultrasonic.h"

/**
 * @Description 初始化定时器5，用于输入捕获
 * @param arr 定时器重装载值
 * @param psc 定时器时钟分频值
 */
void Ultrasonic_Init(u32 arr, u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM5_ICInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	/*第一步:使能外设时钟*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	/*第二步:配置定时器TIM的通道对应的GPIO为复用功能*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/*同时配置好触发超声波信号GPIO的引脚*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOA, GPIO_Pin_5);

	/*第三步:设置GPIO引脚复用*/
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_TIM5);

	/*第四步:设置定时器分频系数,重装载值以及计数模式*/
	TIM_TimeBaseStructure.TIM_Prescaler = psc;			// 设置定时器分频系数
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	// 计数模式为向上计数模式
	TIM_TimeBaseStructure.TIM_Period = arr;				// 设置计数器自动重装载值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);

	/*第五步:初始化TIM5输入捕获参数*/
	TIM5_ICInitStructure.TIM_Channel = TIM_Channel_1;		// CC1S = 01 选择输入端 IC1映射到TI1上
	TIM5_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	// 上升沿捕获
	TIM5_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;// 映射到TI1上
	TIM5_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;		// 配置输入分频,不分频
	TIM5_ICInitStructure.TIM_ICFilter = 0x00;			// IC1F = 0000 配置输入滤波器 不滤波
	TIM_ICInit(TIM5, &TIM5_ICInitStructure);

	/*第六步：开启更新中断和捕获中断*/
	TIM_ITConfig(TIM5, TIM_IT_Update | TIM_IT_CC1, ENABLE);		// 允许更新中断和CC1IE捕获中断

	/*第七步:定时器5中断配置*/
	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	/*第八步:开启定时器*/
	TIM_Cmd(TIM5, ENABLE);
}

/**
 * @Descripiton 开始测量
 */
void Ultrasonic_StartMeasure()
{
	Send = HIGH;
	delay_us(20);
	Send = LOW;
}

/**
 * 输入捕获状态寄存器(用户自定义)
 * TIM5CH1_CAPTURE_STA[7]: 捕获完成标志
 * TIM5CH1_CAPTURE_STA[6]: 捕获到高电平标志
 * TIM5CH1_CAPTURE_STA[5:0]:捕获到高电平后定时器的溢出次数，最多为2^5
 */
u8 TIM5CH1_CAPTURE_STA;

/*用于记录下降沿到来时计数器的计数值的缓存变量*/
u32 TIM5CH1_CAPTURE_VAL;

/**
 * @Description 定时器5中断服务函数
 */
void TIM5_IRQHandler(void)
{
	if((TIM5CH1_CAPTURE_STA & 0X80) == 0)				// 如果还没有捕获完成
	{
		if(TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)	// 没有捕获完成但是定时器溢出了
		{
			if(TIM5CH1_CAPTURE_STA & 0X40)			// 并且是已经捕获到高电平,要继续等待下降沿的到来
			{
				if((TIM5CH1_CAPTURE_STA & 0X3F) == 0X3F)// 高电平持续时间太长了,无法计算到高电平的时间
				{
					TIM5CH1_CAPTURE_STA |= 0X80;	// 只能硬着头皮标记成功捕获了一次
					TIM5CH1_CAPTURE_VAL = 0xFFFFFFFF;// 计数器的计数值就硬着头皮用最大值标记一下
				}
				else
				{
					TIM5CH1_CAPTURE_STA++;		// 在已经捕获到到电平后,每溢出一次,TIM5CH1_CAPTURE_STA值加 1
				}
			}
		}

		if(TIM_GetITStatus(TIM5, TIM_IT_CC1) != RESET)		// 发生了通道1捕获事件
		{
			if(TIM5CH1_CAPTURE_STA & 0X40)			// 如果之前已经捕获到了上升沿,侧表明本次捕获到的是一个下降沿
			{
				DS0 = LED_OFF;
				TIM5CH1_CAPTURE_STA |= 0X80;		// 上升沿和下降沿之间就是一个完整的高电平脉冲,说明捕捉完成了
				TIM5CH1_CAPTURE_VAL = TIM_GetCapture1(TIM5);		// 获取当前的捕获值.
				TIM_OC1PolarityConfig(TIM5, TIM_ICPolarity_Rising);		// CC1P=0 将输入捕获模式设置为上升沿捕获
			}
			else						// 还未开始,第一次捕获上升沿
			{
				DS0 = LED_ON;
				TIM5CH1_CAPTURE_STA = 0;		// 清空标志位和溢出计数值
				TIM5CH1_CAPTURE_VAL = 0;		// 清空下降沿到来时计数值缓存变量
				TIM5CH1_CAPTURE_STA |= 0X40;		// 标记捕获到了上升沿
				TIM_Cmd(TIM5, DISABLE);			// 关闭定时器5
				TIM_SetCounter(TIM5, 0);		// 让计数器重0开始计数
				TIM_OC1PolarityConfig(TIM5, TIM_ICPolarity_Falling);		// CC1P=1 将输入捕获模式设置为下降沿捕获
				TIM_Cmd(TIM5, ENABLE);			// 使能定时器5
			}
		}
	}

	TIM_ClearITPendingBit(TIM5, TIM_IT_CC1 | TIM_IT_Update);	// 退出中断前先清除中断标志位,以便能及时响应下一次中断
}
