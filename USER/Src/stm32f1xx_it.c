#include "stm32f1xx_it.h"
#include "sys.h"
#include "step_motor.h"
#include "gpio.h"



//用户中断函数

void TIM2_IRQHandler(void)
{
	if(TIM2->SR&0X0001) //溢出中断
	{
		//LED0_T;
		motorThr_TimerEvent();
		
	} 
	TIM2->SR&=~(1<<0); //清除中断标志位
}


void TIM3_IRQHandler(void)
{
	if(TIM3->SR&0X0001) //溢出中断
	{
		//LED0_T;
		motorOne_TimerEvent();
		
	} 
	TIM3->SR&=~(1<<0); //清除中断标志位
}


void TIM4_IRQHandler(void)
{
	if(TIM4->SR&0X0001) //溢出中断
	{
		motorTwo_TimerEvent();
	} 
	TIM4->SR&=~(1<<0); //清除中断标志位
}



