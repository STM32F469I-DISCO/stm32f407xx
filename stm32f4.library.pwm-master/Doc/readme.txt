工程介绍：
	1、使用定时器14通道1输出PWM控制LED。
	
硬件资源：
	1、正点原子STM32F4开发板（或者STM32F407最小系统板）。
	2、板载LED灯，DS0。
	
实现效果：
	DS0逐渐变亮，然后又逐渐变暗，一直循环往复。
	
实际意义：
	1、掌握PWM的输出，可以输出任意占空比的方波。
	2、可以驱动很多东西，能够控制好功率。
	
注意事项：
	1、在 Libraries 组中添加：
		stm32f4xx_tim.c
	2、在 stm32f4xx_conf.h 文件中 #include
		stm32f4xx_tim.h
	3、在Edit->Configuration->Editor->Encoding中选择UTF-8（否则会乱码）。
	4、在Edit->Configuration下方的 TAB SIZE 统一设置为8个字符宽。
	5、注意事项3和4请查看readme.png图片。
