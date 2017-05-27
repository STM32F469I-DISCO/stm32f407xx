#ifndef __BSP_KEY_H
#define __BSP_KEY_H

#include "stm32f4xx.h"
#include "bsp_systick.h"

#define KEY0 PEin(4)
#define KEY1 PEin(3)
#define KEY2 PEin(2)
#define WKUP PAin(0)

/* 无按键按下，KEY0按下，KEY1按下，KEY2按下，WKUP按下 */
#define NONE_PRESS 0
#define KEY0_PRESS 1
#define KEY1_PRESS 2
#define KEY2_PRESS 3
#define WKUP_PRESS 4

#define KEY_IS_PRESS 0                                  // 按键已经按下
#define KEY_IS_LOOSEN 1                                 // 按键已经松开

#define KEY_SUPPORT_ALWAYS_PRESS 1                      // 支持连按
#define KEY_NONSUPPORT_ALWAYS_PRESS 0                   // 不支持连按

#define KEY_MODE KEY_NONSUPPORT_ALWAYS_PRESS

void Key_Init(void);
u8 Key_Scan(void);

#endif /* __BSP_KEY_H */
