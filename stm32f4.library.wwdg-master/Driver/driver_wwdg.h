#ifndef __DRIVER_WWDG_H_
#define __DRIVER_WWDG_H_

#include "stm32f4xx.h"
#include "explore_system.h"
#include "driver_led.h"

/*窗口看门狗初始化函数*/
void Wwdg_Init(u32 prer, u16 value);

#endif /*__DRIVER_WWDG_H_*/
