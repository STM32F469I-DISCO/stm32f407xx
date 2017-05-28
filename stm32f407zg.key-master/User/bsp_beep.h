#ifndef __BSP_BEEP_H
#define __BSP_BEEP_H

#include "stm32f4xx.h"
#include "bsp_systick.h"

/* 蜂鸣器开关对应的宏定义 */
#define BEEP_ON 1
#define BEEP_OFF 0

/* 直接操作蜂鸣器的位带操作宏 */
#define BEEP PFout(8)

/* 蜂鸣器初始化 */
void Beep_Init(void);

#endif /* __BSP_BEEP_H */
