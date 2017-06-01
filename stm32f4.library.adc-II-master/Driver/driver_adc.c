#include "driver_adc.h"

/**
 * @Description ADC初始化函数
 */
void Adc_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	ADC_InitTypeDef ADC_InitStructure;

	/*第一步：使能外设时钟*/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3, ENABLE);

	/*第二步：初始化ADC1的通道5对应的I/O口PF7，配置为模拟输入，不带上下拉*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOF, &GPIO_InitStructure);

	/*第三步：ADC复位操作，其实就是先关再开*/
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC3, ENABLE);
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC3, DISABLE);

	/*第四步：设置通用的ADC配置*/
	/*配置ADC模式为独立模式*/
	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
	/*配置ADC采样时间延迟为5个时钟*/
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
	/*配置ADC不使用DMA*/
	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
	/*配置ADC时钟为APB2时钟4分频*/
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div4;
	ADC_CommonInit(&ADC_CommonInitStructure);

	/*第五步：设置专用的ADC配置*/
	/*设置ADC分辨率为12位*/
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
	/*设置ADC为非扫描模式*/
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	/*设置ADC关闭连续转换*/
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
	/*设置ADC禁止外部触发，用软件触发*/
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	/*设置ADC数据对齐方式为右对齐*/
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	/*设置ADC只转换规则序列1*/
	ADC_InitStructure.ADC_NbrOfConversion = 1;
	ADC_Init(ADC3, &ADC_InitStructure);

	/*第六步：开启ADC*/
	ADC_Cmd(ADC3, ENABLE);
}

/**
 * @Description 获取ADC的转换后的值
 * @param ch 通道编号
 * @return 通道ch的转换结果
 */
u16 Adc_GetValue(u8 ch)
{
	/*设置指定ADC的规则组通道，一个序列，采样时间*/
	/*ADC通道,480个周期,提高采样时间可以提高精确度*/
	ADC_RegularChannelConfig(ADC3, ch, 1, ADC_SampleTime_480Cycles);

	/*使能指定的ADC的软件转换启动功能*/
	ADC_SoftwareStartConv(ADC3);

	/*等待转换结束*/
	while (!ADC_GetFlagStatus(ADC3, ADC_FLAG_EOC));

	/*返回最近一次ADC规则组的转换结果*/
	return ADC_GetConversionValue(ADC3);
}

/**
 * @Description 获取ADC通道ch的转换值(转换times次，最后取平均值)
 * @param ch 通道编号
 * @param times 获取次数
 * @return 通道ch的times次转换结果平均值
 */
u16 Adc_GetAverageValue(u8 ch, u8 times)
{
	u32 sum = 0;
	u8 t;
	for (t = 0; t < times; t++)
	{
		sum += Adc_GetValue(ch);
		delay_ms(5);
	}
	return sum / times;
}
