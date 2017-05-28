#include "bsp_beep.h"

/* 驱动版本号：bsp_beep v1.1 */

/**
 * @Description 初始化蜂鸣器
 */
void Beep_Init(void)
{
        GPIO_InitTypeDef GPIO_InitStructure;

        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
        GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
        GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
        GPIO_Init(GPIOF, &GPIO_InitStructure);

        /* 设置GPIOF的Pin8初始值为低电平 */
        GPIO_ResetBits(GPIOF, GPIO_Pin_8);
}
