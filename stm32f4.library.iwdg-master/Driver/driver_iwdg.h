#ifndef __DRIVER_IWDG_H_
#define __DRIVER_IWDG_H_

#include "stm32f4xx.h"

/*初始化独立看门狗*/
void Iwdg_Init(u8 prer, u16 rlr);

#endif /*__DRIVER_IWDG_H_*/
