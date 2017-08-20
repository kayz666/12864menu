#include "timer.h"



//通用定时器 3 中断初始化
//这里时钟选择为 APB1 的 2 倍，而 APB1 为 36M
//arr：自动重装值。
//psc：时钟预分频数
//这里使用的是定时器 3!
void TIM3_Int_Init(u16 arr,u16 psc)
{
	RCC->APB1ENR|=1<<1;  //TIM3 时钟使能
	TIM3->ARR=arr-1; //设定计数器自动重装值//刚好 1ms
	TIM3->PSC=psc-1; //预分频器 7200,得到 10Khz 的计数时钟
	TIM3->DIER|=1<<0; //允许更新中断 
	//TIM3->CR1|=0x01; //使能定时器 3
	MY_NVIC_Init(1,3,TIM3_IRQn,2);//抢占 1，子优先级 3，组 2 
}

void TIM3_ChangeTimer(u16 psc)
{
	TIM3->PSC=psc-1;
}

void TIM3_Enable(void)
{
	TIM3->CR1|=0x01;
}
void TIM3_Disenable(void)
{
	TIM3->CR1&=0x00;
}

void TIM4_Int_Init(u16 arr,u16 psc)
{
	RCC->APB1ENR|=1<<2;  //TIM4 时钟使能
	TIM4->ARR=arr-1; //设定计数器自动重装值//刚好 1ms
	TIM4->PSC=psc-1; //预分频器 7200,得到 10Khz 的计数时钟
	TIM4->DIER|=1<<0; //允许更新中断 
	//TIM4->CR1|=0x01; //使能定时器 3
	MY_NVIC_Init(1,3,TIM4_IRQn,2);//抢占 1，子优先级 3，组 2 
}
void TIM2_Init(void)
{
	RCC->APB1ENR|=1<<0;
	TIM2->ARR=499;
	TIM2->DIER|=1<<0;
	MY_NVIC_Init(1,5,TIM2_IRQn,2);
}

void TIM3_Init(void)
{
	RCC->APB1ENR|=1<<1;
	TIM3->ARR=4;
	TIM3->DIER|=1<<0;
	MY_NVIC_Init(1,3,TIM3_IRQn,2);
}
void TIM4_Init(void)
{
	RCC->APB1ENR|=1<<2;
	TIM4->ARR=4;
	TIM4->DIER|=1<<0;
	MY_NVIC_Init(1,4,TIM4_IRQn,2);
}
void TIM4_ChangeTimer(u16 psc)
{
	TIM4->PSC=psc-1;
}

void TIM4_Enable(void)
{
	TIM4->CR1|=0x01;
}
void TIM4_Disenable(void)
{
	TIM4->CR1&=0x00;
}

void TIM2_ChangeTimer(u16 psc)
{
	TIM2->PSC=psc-1;
}

void TIM2_Enable(void)
{
	TIM2->CR1|=0x01;
}
void TIM2_Disenable(void)
{
	TIM2->CR1&=0x00;
}



void TIM5_PWM_Init(u16 arr, u16 psc)
{
	RCC->APB1ENR|=1<<3;
	TIM5->ARR=arr;
	TIM5->PSC=psc;
	TIM5->CCMR1|=7<<12;
	TIM5->CCMR1|=1<<11;
	TIM5->CCER|=1<<4;
	TIM5->CCER|=1<<5;
	
	TIM5->CR1=0x0080;
	TIM5->CR1|=0X01;
	
}









