#include "driver_random.h"

/**
 * @Description 初始化RNG
 * @return flag 0:成功 1:出错
 */
u8 Random_Init(void)
{
	u16 retry = 0;

	/*开启RNG时钟，来自PLL48CLK(48M)*/
	RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_RNG, ENABLE);

	/*使能RNG*/
	RNG_Cmd(ENABLE);

	/*等待随机数就绪*/
	while (RNG_GetFlagStatus(RNG_FLAG_DRDY) == RESET && retry < 10000)
	{
		retry++;
		delay_us(100);
	}

	/*时间太长了，表示随机数产生器工作不正常*/
	if (retry >= 10000)
		return ERROR;
	return SUCCESSFUL;
}

/**
 * @Description 得到一个32位的随机数
 * @return 获取到的随机数
 */
u32 Random_GetRandomNumber(void)
{
	/*等待随机数就绪*/
	while (RNG_GetFlagStatus(RNG_FLAG_DRDY) == RESET);
	/*返回产生的32位随机数*/
	return RNG_GetRandomNumber();
}

/**
 * @Description 生成[min,max]范围的随机数
 * @return [min,max]范围内的随机数
 */
u32 Random_GetRangeNumber(int min, int max)
{
	return Random_GetRandomNumber() % (max - min + 1) + min;
}
