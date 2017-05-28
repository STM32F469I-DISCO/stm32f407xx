#ifndef __BSP_LCD_H
#define __BSP_LCD_H

#include "stm32f4xx.h"
#include "bsp_usart.h"
#include "bsp_systick.h"
#include "stdlib.h"
#include "string.h"

/* 储存LCD重要参数集的结构体 */
typedef struct
{
        u16 width;
        u16 height;
        u16 id;
        u8 dir;
        u16 wramcmd;
        u16 setxcmd;
        u16 setycmd;
} LCD_InfoTypeDef;

/* LCD重要参数集对象 */
extern LCD_InfoTypeDef lcddev;

/* LCD背光PB15 */
#define	LCD_LED PBout(15)

#define SCREEN_HORIZONTAL 1
#define SCREEN_VERTICAL 0

#define DRAW_DIRECT 1
#define DRAW_REDRAW 0

/* LCD的画笔颜色和背景色 */
extern u16 POINT_COLOR;
extern u16 BACK_COLOR;

/* LCD地址结构体，这里其实只使用到了FSMC控制块中的两个16位的地址 */
typedef struct
{
        /* 操作LCD_REG就相当与通过8080并口时序给LCD写命令 */
        vu16 LCD_REG;                                                   // 0x6C000000 | 0x0000007E)
        /* 操作LCD_RAM就相当与通过8080并口时序给LCD写数据 */
        vu16 LCD_RAM;                                                   // 0x6C000000 | 0x00000080)
} LCD_TypeDef;

/* 使用NOR/SRAM的 Bank1.sector4，地址位HADDR[27,26]=11 A6作为数据命令区分线 */
/* 注意设置时STM32内部会右移一位对齐! 111 1110=0X7E */
#define LCD_BASE ((u32)(0x6C000000 | 0x0000007E))
#define LCD ((LCD_TypeDef*) LCD_BASE)

/* 扫描方向定义 L:Left R:Right U:Up D:Down 2:to */
#define L2R_U2D  0
#define L2R_D2U  1
#define R2L_U2D  2
#define R2L_D2U  3

#define U2D_L2R  4
#define U2D_R2L  5
#define D2U_L2R  6
#define D2U_R2L  7

/* Default Scan Direction 默认的扫描方向 */
#define DFT_SCAN_DIR L2R_U2D

#define WHITE   0xFFFF
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define YELLOW  0xFFE0

void Lcd_WriteCmd(vu16 cmd);
void Lcd_WriteData(vu16 data);
u16 Lcd_ReadData(void);
void Lcd_WriteReg(u16 cmd, u16 data);
u16 Lcd_ReadReg(u16 reg);
void Lcd_WriteRamPrepare(void);
void Lcd_WriteRam(u16 color);
void Lcd_DisplayOn(void);
void Lcd_DisplayOff(void);
void Lcd_Delay(u8 i);

u16 Lcd_ReadPoint(u16 x, u16 y);
void Lcd_SetCursor(u16 Xpos, u16 Ypos);
void Lcd_ScanDir(u8 dir);
void Lcd_DrawPoint(u16 x, u16 y);
void Lcd_FastDrawPoint(u16 x, u16 y, u16 color);
void Lcd_DisplayDir(u8 dir);
void Lcd_SetWindow(u16 sx, u16 sy, u16 width, u16 height);

void Lcd_ClearScreen(u16 color);
void Lcd_Fill(u16 sx, u16 sy, u16 ex, u16 ey, u16 color);
void Lcd_ColorFill(u16 sx, u16 sy, u16 ex, u16 ey, u16 *color);
void Lcd_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2);
void Lcd_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2);
void Lcd_DrawCircle(u16 x0, u16 y0, u8 r);
void Lcd_ShowChar(u16 x, u16 y, u8 num, u8 size, u8 mode);
u8 Lcd_ShowInt(u16 x, u16 y, u32 num, u8 size);
u8 Lcd_ShowFloat(u16 x, u16 y, float num, u8 size);
void Lcd_ShowString(u16 x, u16 y, u16 width, u16 height, u8 size, char *p);
void Lcd_CenterShowString(u16 y, char *p, u8 size);

u32 Lcd_Pow(u8 m, u8 n);

void Lcd_Init(void);

#endif /* __BSP_LCD_H */
