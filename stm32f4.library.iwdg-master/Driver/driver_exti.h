#ifndef __DRIVER_EXTI_H_
#define __DRIVER_EXTI_H_

#include "stm32f4xx.h"
#include "explore_system.h"
#include "explore_systick.h"
#include "explore_usart.h"
#include "driver_led.h"

/*直接读取KEY的位带操作宏*/
#define WKUP PAin(0)

/*外部中断初始化函数*/
void Exti_Init(void);

#endif /*__DRIVER_EXTI_H_*/
