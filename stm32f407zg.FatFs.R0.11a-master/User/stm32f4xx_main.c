#include "stm32f4xx.h"
#include "bsp_systick.h"
#include "bsp_usart.h"
#include "bsp_led.h"
#include "bsp_lcd.h"
#include "bsp_key.h"
#include "bsp_spi.h"
#include "bsp_w25qxx.h"
#include "ff.h"

FRESULT res;
FATFS fs;
FIL fp;
UINT bw;
UINT br;
const char wData[] = "wo shi ni de yan";
char rData[512] = "";

u16 line = 100;


int main(void)
{
        NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
        Systick_Init();
        Usart_Init();
        Led_Init();
        Lcd_Init();
        Key_Init();

        POINT_COLOR = RED;
        BACK_COLOR = WHITE;
        Lcd_ClearScreen(BACK_COLOR);
        Lcd_CenterShowString(50, "FatFs.R0.11a Project", 24);

        POINT_COLOR = BLUE;

        // 挂载文件系统
        res = f_mount(&fs, "0:", 1);
        printf("stm32f4xx_main:\tf_mount1 res = %d\r\n", res);

        if(res == FR_NO_FILESYSTEM)
        {
                res = f_mkfs("0:", 0, 0);
                printf("stm32f4xx_main:\tf_mkfs res = %d\r\n", res);
                res = f_mount(NULL, "0:", 1);
                printf("stm32f4xx_main:\tf_mount2 res = %d\r\n", res);
                res = f_mount(&fs, "0:", 1);
                printf("stm32f4xx_main:\tf_mount3 res = %d\r\n", res);
        }

        res = f_open(&fp, "0:我是.txt", FA_OPEN_ALWAYS | FA_READ | FA_WRITE);
        printf("stm32f4xx_main:\tf_open res = %d\r\n", res);

        if(res == FR_OK)
        {
                res = f_write(&fp, wData, sizeof(wData), &bw);
                printf("stm32f4xx_main:\tf_write res = %d\r\n", res);
                printf("stm32f4xx_main:\tbw = %d\r\n", bw);

                if(res == FR_OK)
                {
                        f_lseek(&fp, 0);
                        res = f_read(&fp, rData, f_size(&fp), &br);
                        printf("stm32f4xx_main:\tf_read res = %d\r\n", res);
                        printf("stm32f4xx_main:\tbr = %d\r\n", br);
                        if(res == FR_OK)
                                printf("stm32f4xx_main:\tdata = %s\r\n\r\n", rData);
                }

                f_close(&fp);

        }

        while(1)
        {
        }
}
