工程介绍：
	1、使用STM32定时器的输入捕获功能测量I/O引脚的高电平持续时间。
	
硬件资源：
	1、正点原子STM32F4开发板（或者STM32F407最小系统板）。
	2、板载LED灯，DS0。
	3、板载独立按键，KEY_UP。
	
实现效果：
	KEY_UP按键按下，可以DS0亮，同时开始计算时间，松手之后将时间值打印在XCOM上。
	并一并显示在LCD屏幕上。
	
实际意义：
	1、在外部中断的基础上可以是同时捕捉时间，可以用于超声波测距中。
	
注意事项：
	1、在 Libraries 组中添加:
		stm32f4xx_tim.c
		stm32f4xx_fsmc.c
	2、在 stm32f4xx_conf.h 文件中 #include
		stm32f4xx_tim.h
		stm32f4xx_fsmc.h
	3、在Edit->Configuration->Editor->Encoding中选择UTF-8（否则会乱码）。
	4、在Edit->Configuration下方的 TAB SIZE 统一设置为8个字符宽。
	5、注意事项3和4请查看readme.png图片。