#ifndef __BSP_LED_H
#define __BSP_LED_H

#include "bsp_systick.h"
#include "stm32f4xx.h"

/* GPIO引脚定义宏 */
#define LED0_GPIO_PORT  GPIOF
#define LED0_GPIO_PIN   GPIO_Pin_9
#define LED0_GPIO_CLK   RCC_AHB1Periph_GPIOF

#define LED1_GPIO_PORT  GPIOF
#define LED1_GPIO_PIN   GPIO_Pin_10
#define LED1_GPIO_CLK   RCC_AHB1Periph_GPIOF

/* 直接操作LED的位带操作宏 */
#define LED0            PFout(9)
#define LED1            PFout(10)

/* LED亮灭对应的宏定义 */
#define LED_ON          (BitAction)0
#define LED_OFF         (BitAction)1

/* LED初始化函数 */
void Led_Init(void); 

#endif /* __BSP_LED_H */
