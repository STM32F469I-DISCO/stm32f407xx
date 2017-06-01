工程介绍：
	1、使用IWDG针对程序跑飞产生复位操作的验证。
	
硬件资源：
	1、正点原子STM32F4开发板（或者STM32F407最小系统板）。
	2、板载LED灯，DS0。
	3、板载独立按键，KEY_UP。
	
实现效果：
	如果持续跑飞DS0会闪烁，但是如果不断的按KEY_UP执行喂狗操作，DS0则会常亮。
	
实际意义：
	1、可以针对程序跑飞而进行强制性的复位操作，能够有效的控制损失。
	
注意事项：
	1、在 Libraries 组中添加：
		stm32f4xx_iwdg.c
		stm32f4xx_exti.c
		stm32f4xx_syscfg.c
	2、在 stm32f4xx_conf.h 文件中 #include
		stm32f4xx_iwdg.h
		stm32f4xx_exti.h
		stm32f4xx_syscfg.h
	3、在Edit->Configuration->Editor->Encoding中选择UTF-8（否则会乱码）。
	4、在Edit->Configuration下方的 TAB SIZE 统一设置为8个字符宽。
	5、注意事项3和4请查看readme.png图片。
