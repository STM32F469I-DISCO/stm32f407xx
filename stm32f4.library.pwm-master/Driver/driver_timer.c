#include "driver_timer.h"

/* @note 改变CCRx的值，就可以改变PWM输出的占空比，改变ARR的值，就可以改变PWM输出的频率*/

/**
 * @Description TIM14 PWM初始化
 * @param arr 自动重装值
 * @param psc 时钟预分频数
 * @note
 * @notice 这里还需要说明一下，对于定时器通道的引脚关系，大家可以查看 STM32F4 对应的数据手册
 */
void TIM14_Init(u32 arr, u32 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

	/*第一步：开启TIM14和PWM通道1对应的GPIO的时钟*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);

	/*第二步；配置GPIO为复用输出*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOF, &GPIO_InitStructure);

	/*第三步：设置GPIO的复用映射*/
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource9, GPIO_AF_TIM14);

	/*第四步：设置定时器的分频和计数值*/
	/*设置定时器的重装载值*/
	TIM_TimeBaseStructure.TIM_Period = arr - 1;
	/*设置定时器的分频系数*/
	TIM_TimeBaseStructure.TIM_Prescaler = psc - 1;
	/*设置定时器为向上计数模式*/
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	/*初始化定时器TIM14*/
	TIM_TimeBaseInit(TIM14, &TIM_TimeBaseStructure);

	/*第五步；设置定时器通道1作PWM输出*/
	/*设置模式是PWM还是输出比较，这里我们是PWM模式。*/
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	/*使能PWM输出到端口*/
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	/*设置定时器输出极性低*/
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	/*PWM 通道设置是通过函数 TIM_OC1Init()~TIM_OC4Init()来设置的*/
	TIM_OC1Init(TIM14, &TIM_OCInitStructure);

	// TIM_OC1PreloadConfig(TIM14, TIM_OCPreload_Enable);
	// TIM_ARRPreloadConfig(TIM14, ENABLE);
	
	/*这里特别提醒，高级定时器TIM1和TIM8虽然和通用定时器类似，但是高级定时器要想输出PWM*/
	/*必须还要设置一个MOE位(TIMx_BDTR 的第15位)，以使能主输出,否则不会输出PWM。*/
	/*库函数设置的函数为：*/
	// TIM_CtrlPWMOutputs(TIM1, ENABLE);

	/*第六步：使能定时器*/
	TIM_Cmd(TIM14, ENABLE);
}
