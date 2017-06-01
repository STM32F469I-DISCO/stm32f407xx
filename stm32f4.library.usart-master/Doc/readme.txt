工程介绍：
	1、使用STM32F407的串口与PC完成简单的通信。
	
硬件资源：
	1、正点原子STM32F4开发板（或者STM32F407最小系统板）。
	2、板载LED，DS0。
	
实现效果：
	MCU每两秒通过串口向PC发送：I can output your input.
	使用串口调试助手XCOM发送数据给MCU，MCU接收到之后原封不动的返回给PC。
	同时每隔300ms闪烁DS0，提示系统正在运行。
	
实际意义：
	1、最基本的通信基础，必须要熟练掌握。
	
注意事项：
	1、需要使用什么外设，就在Libraries组中添加对应stm32f4xx_xxx.c源文件。
	2、同时还需要在stm32f4xx_conf.h文件中#include对应的stm32f4xx_xxx.h头文件。
	3、在Edit->Configuration->Editor->Encoding中选择UTF-8（否则会乱码）。
	4、在Edit->Configuration下方的 TAB SIZE 统一设置为8个字符宽。
	5、注意事项3和4请查看readme.png图片。
