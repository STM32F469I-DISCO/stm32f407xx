#ifndef __DRIVER_RANDOM_H_
#define __DRIVER_RANDOM_H_

#include "stm32f4xx.h"
#include "explore_systick.h"

#define SUCCESSFUL 0
#define ERROR 1

/*初始化RNG*/
u8 Random_Init(void);

/*得到一个32位的随机数*/
u32 Random_GetRandomNumber(void);

/*生成[min,max]范围的随机数*/
u32 Random_GetRangeNumber(int min, int max);

#endif
