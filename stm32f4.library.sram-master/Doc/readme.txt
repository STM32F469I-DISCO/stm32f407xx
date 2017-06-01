工程介绍：
	1、使用FSMC驱动SRAM。
	
硬件资源：
	1、正点原子STM32F4开发板（或者STM32F407最小系统板）。
	2、4.3寸电容屏。
	3、板载SRAM芯片IS62WV51216。
	
实现效果：
	先取出SRAM中预存储的值，显示在屏幕上。
	再重新写入一些新值到SRAM中。
	然后再取出新值，显示在屏幕上。
	
实际意义：
	扩展外部存储设备。
	
注意事项：
	1、在 Libraries 组中添加：
		stm32f4xx_fsmc.c
	2、在 stm32f4xx_conf.h 文件中 #include
		stm32f4xx_fsmc.h
	3、在Edit->Configuration->Editor->Encoding中选择UTF-8（否则会乱码）。
	4、在Edit->Configuration下方的 TAB SIZE 统一设置为8个字符宽。
	5、注意事项3和4请查看readme.png图片。
	6、本程序的LCD驱动只支持4.3寸电容屏，主控IC为NT35510。
