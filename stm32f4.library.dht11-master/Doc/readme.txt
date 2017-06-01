工程介绍：
	1、使用温湿度传感器获取环境参数。
	
硬件资源：
	1、正点原子STM32F4开发板（或者STM32F407最小系统板）。
	2、DHT11模块（测量结果没有小数部分）。
	
实现效果：
	在LCD上显示温湿度信息，格式：humdity = 64.0 % temperature = 31.0 C。
	
实际意义：
	1、测量环境的温湿度。
	
注意事项：
	1、需要使用什么外设，就在Libraries组中添加对应stm32f4xx_xxx.c源文件。
	2、同时还需要在stm32f4xx_conf.h文件中#include对应的stm32f4xx_xxx.h头文件。
	3、在Edit->Configuration->Editor->Encoding中选择UTF-8（否则会乱码）。
	4、在Edit->Configuration下方的 TAB SIZE 统一设置为8个字符宽。
	5、注意事项3和4请查看readme.png图片。
