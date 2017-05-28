#include "bsp_led.h"

/* 驱动版本号：bsp_led v1.1 */

/**
 * @Description 初始化LED
 */
void Led_Init(void)
{
        /* 创建一个GPIO初始化结构体，用于初始化控制LED的GPIO */
        GPIO_InitTypeDef GPIO_InitStructure;
        
        /* 第一步：使能GPIOF时钟 */
        RCC_AHB1PeriphClockCmd(LED0_GPIO_CLK, ENABLE);
        RCC_AHB1PeriphClockCmd(LED1_GPIO_CLK, ENABLE);
        
        /* 第二步：配置GPIO引脚模式 */
        GPIO_InitStructure.GPIO_Pin = LED0_GPIO_PIN;                    // 设置要配置引脚
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;                   // 设置为输出模式
        GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;                  // 设置为推挽输出
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;              // 设置输出速率为100M
        GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;                    // 设置为上拉模式
        GPIO_Init(LED0_GPIO_PORT, &GPIO_InitStructure);                 // 初始化GPIO
        
        GPIO_InitStructure.GPIO_Pin = LED1_GPIO_PIN;
        GPIO_Init(LED1_GPIO_PORT, &GPIO_InitStructure);
        
        /* 第三步：配置完成之后关闭LED灯 */
        GPIO_WriteBit(LED0_GPIO_PORT, LED0_GPIO_PIN, LED_OFF);
        GPIO_WriteBit(LED1_GPIO_PORT, LED1_GPIO_PIN, LED_OFF);
}
