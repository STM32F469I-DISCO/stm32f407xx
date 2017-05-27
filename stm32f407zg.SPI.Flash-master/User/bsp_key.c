#include "bsp_key.h"

/* 驱动版本号：bsp_key v1.2 */

/**
 * @Description 初始化按键
 */
void Key_Init(void)
{
        GPIO_InitTypeDef GPIO_InitStructure;

        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
        GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
        GPIO_Init(GPIOE, &GPIO_InitStructure);

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
        GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/**
 * @Description 按键扫描函数
 * @param mode  模式选择参数(是否支持连按)
 * @return      按键对应键值
 */
u8 Key_Scan(void)
{
        /* 按键按松开标志 */
        static u8 key_up = KEY_IS_LOOSEN;

        /* 如果设置了支持连按，则每次进入此函数强制标志按键已松开 */
        if(KEY_MODE)
                key_up = KEY_IS_LOOSEN;

        /* 在按键已松开的情况下才可以捕捉按键键值 */
        if(key_up && (KEY0 == 0 || KEY1 == 0 || KEY2 == 0 || WKUP == 1))
        {
                /* 延时消抖 */
                delay_ms(10);
                /* 捕捉到按键时，标记按键已经按下 */
                key_up = KEY_IS_PRESS;
                if(KEY0 == 0)
                        return KEY0_PRESS;
                else if(KEY1 == 0)
                        return KEY1_PRESS;
                else if(KEY2 == 0)
                        return KEY2_PRESS;
                else if(WKUP == 1)
                        return WKUP_PRESS;
        }
        else if(KEY0 == 1 && KEY1 == 1 && KEY2 == 1 && WKUP == 0)
        {
                /* 不管是否按下标志key_up为何值，只要没有一个按键按下，将按键按松开标志标记为按键已松开 */
                key_up = KEY_IS_LOOSEN;
        }

        return NONE_PRESS;
}
