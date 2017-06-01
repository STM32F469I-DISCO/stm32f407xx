#ifndef __DRIVER_TEMPERATURE_H_
#define __DRIVER_TEMPERATURE_H_

#include "stm32f4xx.h"
#include "explore_system.h"
#include "explore_systick.h"

/*数据传输引脚配置*/
#define DHT11_GPIO_PORT GPIOE
#define DHT11_GPIO_CLK RCC_AHB1Periph_GPIOE
#define DHT11_GPIO_PIN GPIO_Pin_1

void DHT_Init(void);							// HDT11初始化
void DHT_SetGpioIn(void);						// 设置与DHT传输信号的GPIO为输入模式
void DHT_SetGpioOut(void);						// 设置与DHT传输信号的GPIO为输出模式
void DHT_ReadData(void);						// 读取温湿度信息
u8 DHT_ReadDataBit(void);						// 读取DHT11返回的字节信息

#endif /* __DRIVER_TEMPERATURE_H_ */
