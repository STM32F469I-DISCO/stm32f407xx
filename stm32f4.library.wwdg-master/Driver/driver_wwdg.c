#include "driver_wwdg.h"

/**
 * @Description 窗口看门狗初始化函数
 * @param fprer 窗口看门狗分频系数 WWDG_Prescaler_1(2、4、8)
 * @param value 窗口看门狗上窗口值 value<=0x7f
 * @return null 无返回值
 */
void Wwdg_Init(u32 fprer, u16 value)
{
	NVIC_InitTypeDef NVIC_InitStructure;

	/*第一步：使能外设时钟*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);

	/*第二步：配置窗口看门狗分频数和上窗口值*/
	WWDG_SetPrescaler(fprer);
	WWDG_SetWindowValue(value);

	/*第三步：设置看门狗初始值并使能看门狗*/
	WWDG_Enable(0x7f);

	/*第四步：配置看门狗中断属性*/
	NVIC_InitStructure.NVIC_IRQChannel = WWDG_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	/*清除提前唤醒中断标志位*/
	WWDG_ClearFlag();
	/*开启提前唤醒中断*/
	WWDG_EnableIT();
}

/**
 * #Description 窗口看门狗中断服务函数
 */
void WWDG_IRQHandler(void)
{
	/*重设窗口看门狗计数值*/
	WWDG_SetCounter(0x7f);
	/*清除提前唤醒中断标志位*/
	WWDG_ClearFlag();
	/*窗口看门狗的中断使得DS1闪烁*/
	DS1 = !DS1;
}
