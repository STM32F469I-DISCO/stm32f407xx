工程介绍：
        1、正点原子STM32F4探索者开发板SPI读写Flash实验。

硬件资源：
        1、正点原子STM32F4探索者开发板。
        2、板载LED灯，DS0、DS1。
        3、USB转串口线。
        4、4.3寸LCD液晶屏。
        5、板载Flash芯片W25Q128。

实现效果：
        LCD显示FatFs.R0.11a Project。

运用知识：
        1、SPI全双工通信。
        2、Flash内部寄存器个读写时序。
        3、FatFs文件系统移植。

驱动版本：
┌-------------------------------┬---------------┐
|            Filename           |    Version    |
├-------------------------------┼---------------┤
| 01.bsp_systick.c              | v1.1          |
├-------------------------------┼---------------┤
| 02.bsp_usart.c                | v1.2          |
├-------------------------------┼---------------┤
| 03.bsp_led.c                  | v1.1          |
├-------------------------------┼---------------┤
| 04.bsp_lcd.c                  | v1.3          |
├-------------------------------┼---------------┤
| 05.bsp_spi.c                  | v1.3          |
├-------------------------------┼---------------┤
| 06.bsp_key.c                  | v1.2          |
├-------------------------------┼---------------┤
| 07.bsp_w25qxx.c               | v1.4          |
└-------------------------------┴---------------┘

注意事项：
        1、TAB键为8个字符宽，并且使用空格填充，使用的编码为UTF-8。