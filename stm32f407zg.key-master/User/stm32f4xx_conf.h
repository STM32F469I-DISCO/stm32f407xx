#ifndef __STM32F4xx_CONF_H
#define __STM32F4xx_CONF_H

/* 工程用到了哪些资源，就添加对应的头文件 */
#include "misc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_usart.h"
#include "stm32f4xx_fsmc.h"

#ifdef USE_FULL_ASSERT
#define assert_param(expr) ((expr) ? (void)0 : assert_failed((uint8_t *)__FILE__, __LINE__))
void assert_failed(uint8_t* file, uint32_t line);
#else
#define assert_param(expr) ((void)0)
#endif /* USE_FULL_ASSERT */

#endif /* __STM32F4xx_CONF_H */
