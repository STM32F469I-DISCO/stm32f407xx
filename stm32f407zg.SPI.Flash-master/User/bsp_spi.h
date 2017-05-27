#ifndef _BSP_SPI_H
#define _BSP_SPI_H

#include "stm32f4xx.h"
#include "bsp_systick.h"

#define USING_SPI1

/* 使用SPI1 */
#ifdef USING_SPI1
#define SPIx                    SPI1
#define RCC_APBxPeriph_SPIx     RCC_APB2Periph_SPI1
#define SPI_APBxPeriphClockCmd  RCC_APB2PeriphClockCmd
#define SPI_APBxPeriphResetCmd  RCC_APB2PeriphResetCmd

#define SPI_MOSI_GPIO_PORT      GPIOB
#define SPI_MOSI_GPIO_CLK       RCC_AHB1Periph_GPIOB
#define SPI_MOSI_PIN            GPIO_Pin_5
#define SPI_MOSI_AF             GPIO_AF_SPI1
#define SPI_MOSI_SOURCE         GPIO_PinSource5

#define SPI_MISO_GPIO_PORT      GPIOB
#define SPI_MISO_GPIO_CLK       RCC_AHB1Periph_GPIOB
#define SPI_MISO_PIN            GPIO_Pin_4
#define SPI_MISO_AF             GPIO_AF_SPI1
#define SPI_MISO_SOURCE         GPIO_PinSource4

#define SPI_SCK_GPIO_PORT       GPIOB
#define SPI_SCK_GPIO_CLK        RCC_AHB1Periph_GPIOB
#define SPI_SCK_PIN             GPIO_Pin_3
#define SPI_SCK_AF              GPIO_AF_SPI1
#define SPI_SCK_SOURCE          GPIO_PinSource3
#endif /* USING_SPI1 */

void Spi_Init(void);
void Spi_SetSpeed(u8 SpeedSet);
u8 Spi_ReadWriteByte(u8 data);

#endif /* _BSP_SPI_H */
