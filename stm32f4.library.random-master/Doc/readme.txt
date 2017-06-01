工程介绍：
	1、随机数发生实验。
	
硬件资源：
	1、正点原子STM32F4开发板（或者STM32F407最小系统板）。
	2、4.3寸电容屏。
	
实现效果：
	在屏幕中显示产生的随机数。
	
实际意义：
	1、可以用于产生硬件随机数。
	2、2048的2或4的生成位置，俄罗斯方块的形状生成都需要随机数。
	
注意事项：
	1、在 Libraries 组中添加：
		stm32f4xx_fsmc.c
		stm32f4xx_rng.c
	2、在 stm32f4xx_conf.h 文件中 #include
		stm32f4xx_fsmc.h
		stm32f4xx_rng.h
	3、在Edit->Configuration->Editor->Encoding中选择UTF-8（否则会乱码）。
	4、在Edit->Configuration下方的 TAB SIZE 统一设置为8个字符宽。
	5、注意事项3和4请查看readme.png图片。
