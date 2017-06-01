#ifndef __DRIVE_LCD1602_H_
#define __DRIVE_LCD1602_H_

#include "stm32f4xx.h"
#include "explore_systick.h"

// 控制引脚对应的宏
#define RS_GPIO_PORT GPIOE
#define RS_GPIO_CLK RCC_AHB1Periph_GPIOE
#define RS_GPIO_PIN GPIO_Pin_13

#define RW_GPIO_PORT GPIOE
#define RW_GPIO_CLK RCC_AHB1Periph_GPIOE
#define RW_GPIO_PIN GPIO_Pin_12

#define E_GPIO_PORT GPIOE
#define E_GPIO_CLK RCC_AHB1Periph_GPIOE
#define E_GPIO_PIN GPIO_Pin_11

// 数据引脚对应的宏
#define DATA0_GPIO_PORT GPIOE
#define DATA0_GPIO_CLK RCC_AHB1Periph_GPIOE
#define DATA0_GPIO_PIN GPIO_Pin_10

#define DATA1_GPIO_PORT GPIOE
#define DATA1_GPIO_CLK RCC_AHB1Periph_GPIOE
#define DATA1_GPIO_PIN GPIO_Pin_9

#define DATA2_GPIO_PORT GPIOE
#define DATA2_GPIO_CLK RCC_AHB1Periph_GPIOE
#define DATA2_GPIO_PIN GPIO_Pin_8

#define DATA3_GPIO_PORT GPIOE
#define DATA3_GPIO_CLK RCC_AHB1Periph_GPIOE
#define DATA3_GPIO_PIN GPIO_Pin_7

#define DATA4_GPIO_PORT GPIOD
#define DATA4_GPIO_CLK RCC_AHB1Periph_GPIOD
#define DATA4_GPIO_PIN GPIO_Pin_1

#define DATA5_GPIO_PORT GPIOD
#define DATA5_GPIO_CLK RCC_AHB1Periph_GPIOD
#define DATA5_GPIO_PIN GPIO_Pin_0

#define DATA6_GPIO_PORT GPIOD
#define DATA6_GPIO_CLK RCC_AHB1Periph_GPIOD
#define DATA6_GPIO_PIN GPIO_Pin_15

#define DATA7_GPIO_PORT GPIOD
#define DATA7_GPIO_CLK RCC_AHB1Periph_GPIOD
#define DATA7_GPIO_PIN GPIO_Pin_14

void LCD1602_Init(void);						// LCD1602 初始化函数
void LCD1602_RS(u8 a);							// LCD1602 数据/命令选择
void LCD1602_RW(u8 a);							// LCD1602 读/写选择
void LCD1602_E(u8 a);							// LCD1602 使能位
void LCD_WriteCmd(u8 cmd);						// LCD1602 写命令
void LCD_WriteDat(u8 dat);						// LCD1602 写数据
void LCD1602_WriteString(u8 x, u8 y, char* str);			// LCD1602 显示字符串

#endif /* __DRIVE_LCD1602_H_ */
