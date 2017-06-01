工程介绍：
	1、使用ADC捕捉I/O引脚的电压值。
	
硬件资源：
	1、正点原子STM32F4开发板（或者STM32F407最小系统板）。
	2、4.3寸电容屏。
	3、电压表。
	4、一个带有滑动变阻器的电路小模块（电路中的某一个点的电压值可以调节即可）。
	
实现效果：
	通过内部ADC捕捉GPIO引脚的电压值，输出到屏幕上。
	
实际意义：
	掌握ADC的使用，ADC作为信号采集的一个很重要的方法。
	一般的传感器都是通过电压信号反馈物理量的信息。
	而ADC的作用就是去捕捉这些电压信号的值。
	
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
