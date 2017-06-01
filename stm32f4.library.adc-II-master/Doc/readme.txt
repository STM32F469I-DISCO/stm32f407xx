工程介绍：
	1、使用ADC采集光敏电阻两端的电压值。
	
硬件资源：
	1、正点原子STM32F4开发板（或者STM32F407最小系统板）。
	2、4.3寸电容屏。
	
实现效果：
	在屏幕中显示光敏电阻的电压值。
	
实际意义：
	1、进一步加深ADC的了解和使用。
	
注意事项：
	1、在 Libraries 组中添加：
		stm32f4xx_fsmc.c
		stm32f4xx_adc.c
	2、在 stm32f4xx_conf.h 文件中 #include
		stm32f4xx_fsmc.h
		stm32f4xx_adc.h
	3、在Edit->Configuration->Editor->Encoding中选择UTF-8（否则会乱码）。
	4、在Edit->Configuration下方的 TAB SIZE 统一设置为8个字符宽。
	5、注意事项3和4请查看readme.png图片。
