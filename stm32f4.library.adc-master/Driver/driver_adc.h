#ifndef __DRIVER_ADC_H_
#define __DRIVER_ADC_H_

#include "stm32f4xx.h"
#include "explore_system.h"
#include "explore_systick.h"

/*ADC初始化函数*/
void Adc_Init(void);

/*获取ADC的转换后的值*/
u16 Adc_GetValue(u8 ch);

/*获取ADC通道ch的转换值(转换times次，最后取平均值)*/
u16 Adc_GetAverageValue(u8 ch, u8 times);

#endif /*__DRIVER_ADC_H_*/
