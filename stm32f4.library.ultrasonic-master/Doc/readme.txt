工程介绍：
	1、这个例程是输入捕获例程的实际应用。
	2、使用输入捕获获取到超声波的往返时间,便可以计算到距离,计算公式为：s = v*t/2。
	
硬件资源：
	1、正点原子STM32F4开发板（或者STM32F407最小系统板）。
	2、HC-SR04超声波模块，PA5触发，PA0捕捉。
	
实现效果：
	测量出来的距离值通过串口打印在XCOM上。
	
实际意义：
	1、测距。
	
注意事项：
	1、在 Libraries 组中添加：
		stm32f4xx_fsmc.c
		stm32f4xx_tim.c
	2、在 stm32f4xx_conf.h 文件中 #include：
		stm32f4xx_fsmc.h
		stm32f4xx_tim.h
	3、在Edit->Configuration->Editor->Encoding中选择UTF-8（否则会乱码）。
	4、在Edit->Configuration下方的 TAB SIZE 统一设置为8个字符宽。
	5、注意事项3和4请查看readme.png图片。
