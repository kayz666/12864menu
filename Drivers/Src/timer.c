#include "timer.h"



//通用定时器 3 中断初始化
//这里时钟选择为 APB1 的 2 倍，而 APB1 为 36M
//arr：自动重装值。
//psc：时钟预分频数
//这里使用的是定时器 3!
void TIM3_Int_Init(u16 arr,u16 psc)
{
	RCC->APB1ENR|=1<<1;  //TIM3 时钟使能
	TIM3->ARR=arr; //设定计数器自动重装值//刚好 1ms
	TIM3->PSC=psc; //预分频器 7200,得到 10Khz 的计数时钟
	TIM3->DIER|=1<<0; //允许更新中断 
	TIM3->CR1|=0x01; //使能定时器 3
	MY_NVIC_Init(1,3,TIM3_IRQn,2);//抢占 1，子优先级 3，组 2 
}





















