#include "driver_iwdg.h"

/**
 * @Description 初始化独立看门狗
 * @param prer 设置独立看门狗时钟分频系数 0<prer<7 分别对应 4、8、16、32、64、128、256分频
 * @param rlr 设置重装载值 rlr<0xfff
 * @return null 无返回值
 */
void Iwdg_Init(u8 prer, u16 rlr)
{
	/*取消写保护*/
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
	/*设置分频器的分频数*/
	IWDG_SetPrescaler(prer);
	/*设置独立看门狗的重装载值*/
	IWDG_SetReload(rlr);
	/*喂狗（此操作会启动写保护功能）*/
	IWDG_ReloadCounter();
	/*使能看门狗*/
	IWDG_Enable();
}
