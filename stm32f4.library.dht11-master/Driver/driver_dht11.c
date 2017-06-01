#include "driver_dht11.h"

u8 DHT11_StatusCode;
u8 DHT11_Data[5];

/**
 * @Description DHT11初始化函数。
 */
void DHT_Init(void)
{
	RCC_AHB1PeriphClockCmd(DHT11_GPIO_CLK, ENABLE);			// 使能GPIO时钟
	DHT_SetGpioOut();						// 设置为输出模式
	GPIO_SetBits(DHT11_GPIO_PORT, DHT11_GPIO_PIN);			// 并输出高电平(总线空闲状态为高电平)
	delay_ms(1000);							// 等待1秒越过不稳定状态
}

/**
 * @Description 设置与DHT传输信号的GPIO为输入模式，接收DHT传递过来的信息。
 */
void DHT_SetGpioIn(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;				// 创建一个GPIO初始化结构体
	GPIO_InitStructure.GPIO_Pin = DHT11_GPIO_PIN;			// 设置要配置引脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;			// 设置为通用输入
	GPIO_Init(DHT11_GPIO_PORT, &GPIO_InitStructure);		// 通过GPIO_InitStructure结构体初始化
}

/**
 * @Description 设置与DHT传输信号的GPIO为输出模式，发送控制信号给DHT模块。
 */
void DHT_SetGpioOut(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;				// 创建一个GPIO初始化结构体
	GPIO_InitStructure.GPIO_Pin = DHT11_GPIO_PIN;			// 设置要配置引脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;			// 设置为输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;			// 设置为推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;		// 设置输出速率为100M
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;			// 设置为上拉模式
	GPIO_Init(DHT11_GPIO_PORT, &GPIO_InitStructure);		// 通过GPIO_InitStructure结构体初始化
}

/**
 * @Description 读取温湿度信息
 * 1. 总线空闲状态为高电平,主机把总线拉低等待DHT11响应,主机把总线拉低必须大于18毫秒,保证DHT11能检测到起始信号。
 * 2. 主机发送开始信号结束后,延时等待20-40us后, 读取DHT11的响应信号,主机发送开始信号后,要切换到输入模式。
 * 3. DHT11接收到主机的开始信号后,等待主机开始信号结束(转为输入模式或者输出高电平),然后发送80us低电平响应信号。
 * 4. DHT11发送响应信号后,再把总线拉高80us,准备发送数据
 */
void DHT_ReadData()
{
	u8 dht_in;							// 定义一个字节数据
	u8 i;								// 定义循环变量 i
	u8 dht_check_sum;
	DHT11_StatusCode = 0;						// 状态码默认为0

	GPIO_ResetBits(DHT11_GPIO_PORT, DHT11_GPIO_PIN);		// 第一步:主机把总线拉低必须大于18ms
	delay_ms(20);							// 这里拉低了20ms

	GPIO_SetBits(DHT11_GPIO_PORT, DHT11_GPIO_PIN);			// 第二步:主机发送开始信号结束,延时等待20-40us
	delay_us(40);							// 这里置为高电平结束开始信号,同时延时了40us

	DHT_SetGpioIn();						// 第三步:DH11发送80us低电平响应信号
	dht_in = GPIO_ReadInputDataBit(DHT11_GPIO_PORT, DHT11_GPIO_PIN);
	if(dht_in)
	{
		DHT11_StatusCode = 1;
		return;
	}
	delay_us(80);							// 80us之后再读一次

	dht_in = GPIO_ReadInputDataBit(DHT11_GPIO_PORT, DHT11_GPIO_PIN);							// 第四步：DH11再把总线拉高80us,准备发送数据
	if(!dht_in)
	{
		DHT11_StatusCode = 2;
		return;
	}
	delay_us(80);							// 80us之后开始接受温湿度的值

	for(i = 0; i < 5; i++)
	{
		DHT11_Data[i] = DHT_ReadDataBit();
	}

	DHT_SetGpioOut();						// 设置引脚为输出模式
	GPIO_SetBits(DHT11_GPIO_PORT, DHT11_GPIO_PIN);			// 空闲时间保持传输线为高电平

	/*根据DHT11的校验规范,校验传输是否出现差错*/
	dht_check_sum = DHT11_Data[0] + DHT11_Data[1] + DHT11_Data[2] + DHT11_Data[3];

	if(DHT11_Data[4] != dht_check_sum)				// 如果校验出错了
	{
		DHT11_StatusCode = 3;					// 则设置状态码的值为3
	}
}

/**
 * @Description 读取DHT11返回的字节信息
 * @note 每一bit数据都以50us低电平时隙开始,高电平的长短定了数据位是0还是1。
 * @note 高电平26-28us为0, 高电平为70us为高电平.
 */
u8 DHT_ReadDataBit()
{
	u8 i = 0;
	u8 result = 0;
	for(i = 0; i < 8; i++)
	{
		while(GPIO_ReadInputDataBit(DHT11_GPIO_PORT, DHT11_GPIO_PIN) == 0)
			;
		delay_us(30);
		if(GPIO_ReadInputDataBit(DHT11_GPIO_PORT, DHT11_GPIO_PIN) == 1)
		{
			result |= (1 << (7 - i));
		}
		while(GPIO_ReadInputDataBit(DHT11_GPIO_PORT, DHT11_GPIO_PIN) == 1)
			;
	}
	return result;
}
