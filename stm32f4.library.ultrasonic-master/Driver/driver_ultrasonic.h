#ifndef __DRIVER_ULTRASONIC_H_
#define __DRIVER_ULTRASONIC_H_

#include "stm32f4xx.h"
#include "explore_system.h"
#include "explore_systick.h"
#include "driver_led.h"

#define LOW 0
#define HIGH 1

#define Send PAout(5)

/*初始化定时器5,用于输入捕获*/
void Ultrasonic_Init(u32 arr, u16 psc);
void Ultrasonic_StartMeasure(void);

#endif /* __DRIVER_ULTRASONIC_H_ */
