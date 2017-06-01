工程介绍：
	1、验证WWDG工作原理的简单测试。
	
硬件资源：
	1、正点原子STM32F4开发板（或者STM32F407最小系统板）。
	2、板载LED灯，DS0、DS1。
	
实现效果：
	DS0亮1s之后不再亮，DS1大概闪烁频率为20次/s。
	
实际意义：
	1、WWDG适合更精确的控制程序的不正常执行，不是直接复位，而是具备特定的处理程序。
	
注意事项：
	1、在 Libraries 组中添加：
		stm32f4xx_wwdg.c
	2、在 stm32f4xx_conf.h 文件中 #include
		stm32f4xx_wwdg.h
	3、在Edit->Configuration->Editor->Encoding中选择UTF-8（否则会乱码）。
	4、在Edit->Configuration下方的 TAB SIZE 统一设置为8个字符宽。
	5、注意事项3和4请查看readme.png图片。
