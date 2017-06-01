#ifndef __DRIVER_TIMER_H_
#define __DRIVER_TIMER_H_

#include "stm32f4xx.h"
#include "explore_usart.h"
#include "driver_led.h"

/*初始化TIM3函数*/
void TIM3_Init(u16 arr, u16 psc);

#endif /*__DRIVER_TIMER_H_*/
