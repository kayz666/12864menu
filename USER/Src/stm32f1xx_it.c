#include "sys.h"
#include "gpio.h"


//用户中断函数

void TIM3_IRQHandler(void)
{
	if(TIM3->SR&0X0001) //溢出中断
	{
		LED0=!LED0; 
	} 
	TIM3->SR&=~(1<<0); //清除中断标志位
}





