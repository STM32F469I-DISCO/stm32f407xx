#ifndef __BSP_USART_H
#define __BSP_USART_H

#include "stdio.h"
#include "stm32f4xx.h"

#define USING_USART2

/* 使用USART1 PA9-TX PA10-RX */
#ifdef USING_USART1
#define USART                   USART1
#define USART_CLK               RCC_APB2Periph_USART1
#define USART_APBxClkCmd        RCC_APB2PeriphClockCmd

#define USART_TX_GPIO_PORT      GPIOA
#define USART_TX_GPIO_CLK       RCC_AHB1Periph_GPIOA
#define USART_TX_PIN            GPIO_Pin_9
#define USART_TX_AF             GPIO_AF_USART1
#define USART_TX_SOURCE         GPIO_PinSource9

#define USART_RX_GPIO_PORT      GPIOA
#define USART_RX_GPIO_CLK       RCC_AHB1Periph_GPIOA
#define USART_RX_PIN            GPIO_Pin_10
#define USART_RX_AF             GPIO_AF_USART1
#define USART_RX_SOURCE         GPIO_PinSource10

#define USART_IRQHandler        USART1_IRQHandler
#define USART_IRQ               USART1_IRQn
#endif /* USING_USART1 */

/* 使用USART2 PA2-TX PA3-RX */
#ifdef USING_USART2
#define USART                   USART2
#define USART_CLK               RCC_APB1Periph_USART2
#define USART_APBxClkCmd        RCC_APB1PeriphClockCmd

#define USART_TX_GPIO_PORT      GPIOA
#define USART_TX_GPIO_CLK       RCC_AHB1Periph_GPIOA
#define USART_TX_PIN            GPIO_Pin_2
#define USART_TX_AF             GPIO_AF_USART2
#define USART_TX_SOURCE         GPIO_PinSource2

#define USART_RX_GPIO_PORT      GPIOA
#define USART_RX_GPIO_CLK       RCC_AHB1Periph_GPIOA
#define USART_RX_PIN            GPIO_Pin_3
#define USART_RX_AF             GPIO_AF_USART2
#define USART_RX_SOURCE         GPIO_PinSource3

#define USART_IRQHandler        USART2_IRQHandler
#define USART_IRQ               USART2_IRQn
#endif /* USING_USART2 */

#define USART_BAUDRATE          115200                  // 串口波特率
#define USART_REC_LEN           200                     // 定义最大接收字节数

extern u8 USART_RX_BUF[USART_REC_LEN];                  // 接收缓冲数组
extern u16 USART_RX_STA;                                // 接收状态标记

void Usart_Init(void);                                  // 串口初始化函数

#endif /* __BSP_USART_H */
