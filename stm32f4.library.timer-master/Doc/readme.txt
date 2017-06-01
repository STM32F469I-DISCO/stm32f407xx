工程介绍：
	1、使用定时器3实现精确的延时。
	
硬件资源：
	1、正点原子STM32F4开发板（或者STM32F407最小系统板）。
	2、板载LED灯，DS0、DS1。
	
实现效果：
	实现DS0和DS1均亮0.5s灭0.5s，可以通过串口时间戳观察。
	只不过DS0是通过滴答定时器实现精确的延时。
	DS1是通过定时器3实现精确的延时。
	
实际意义：
	1、掌握STM32的定时器原理，为输入捕获和PWM输出打好基础。
	
注意事项：
	1、在 Libraries 组中添加：
		stm32f4xx_tim.c
	2、在 stm32f4xx_conf.h 文件中 #include
		stm32f4xx_tim.h
	3、在Edit->Configuration->Editor->Encoding中选择UTF-8（否则会乱码）。
	4、在Edit->Configuration下方的 TAB SIZE 统一设置为8个字符宽。
	5、注意事项3和4请查看readme.png图片。
