#include "stm32f4xx_it.h"

void NMI_Handler(void)
{

}

void HardFault_Handler(void)
{
        printf(">>>>>>>> HardFault_Handler <<<<<<<<");
        while(1)
        {
        }
}

void MemManage_Handler(void)
{
        printf(">>>>>>>> MemManage_Handler <<<<<<<<");
        while(1)
        {
        }
}

void BusFault_Handler(void)
{
        printf(">>>>>>>> BusFault_Handler <<<<<<<<");
        while(1)
        {
        }
}

void UsageFault_Handler(void)
{
        printf(">>>>>>>> UsageFault_Handler <<<<<<<<");
        while(1)
        {
        }
}

void SVC_Handler(void)
{

}

void DebugMon_Handler(void)
{

}

void PendSV_Handler(void)
{

}

void SysTick_Handler(void)
{

}

void PPP_IRQHandler(void)
{

}
