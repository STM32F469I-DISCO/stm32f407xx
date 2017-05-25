#include "stm32f4xx.h"
#include "bsp_systick.h"
#include "bsp_usart.h"
#include "bsp_led.h"
#include "bsp_lcd.h"
#include "bsp_key.h"
#include "bsp_spi.h"
#include "ff.h"

const char wData[] = "wo shi ni de yan";
char rData[4096] = "";

FATFS fs;
FIL fil;
BYTE work[_MAX_SS];

UINT bw;
UINT br;

int main(void)
{
        FRESULT res;

        NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
        Systick_Init();
        Usart_Init();
        Led_Init();
        Lcd_Init();
        Key_Init();

        POINT_COLOR = RED;
        BACK_COLOR = WHITE;
        Lcd_ClearScreen(BACK_COLOR);
        Lcd_CenterShowString(50, "FatFs Project", 24);

        res = f_mount(&fs, "0:", 1);

        printf("stm32f4xx_main:\tf_mount function return = %d\r\n", res);

//        if(res == FR_NO_FILESYSTEM)
//        {
//                printf("\r\nf_mkfs res =%d", res);
//                //格式化后要取消挂载再重新挂载文件系统
//                res = f_mount(NULL, "0:", 1);
//                res = f_mount(&fs, "0:", 1);

//                printf("\r\nsecond f_mount res =%d", res);
//        }

//        res = f_open(&fil, "1:Demo.txt", FA_OPEN_ALWAYS | FA_READ | FA_WRITE);
//        printf("\r\nf_open res =%d", res);

//        if(res == FR_OK)
//        {
//                res = f_write(&fil, wData, sizeof(wData), &bw);
//                printf("\r\nbw= %d", bw);

//                if(res == FR_OK)
//                {
//                        f_lseek(&fil, 0);
//                        res = f_read(&fil, rData, f_size(&fil), &br);
//                        if(res == FR_OK)
//                        {
//                                printf("OK");
//                        }
//                }

//                f_close(&fil);

//        }

        while(1)
        {

        }
}
