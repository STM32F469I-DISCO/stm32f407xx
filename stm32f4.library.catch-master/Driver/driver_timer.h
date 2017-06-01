#ifndef __DRIVER_TIMER_H_
#define __DRIVER_TIMER_H_

#include "stm32f4xx.h"
#include "driver_led.h"
#include "driver_lcd.h"

/*初始化定时器5，用于输入捕获*/
void TIM5_Init(u32 arr, u16 psc);

#endif /*__DRIVER_TIMER_H_*/
