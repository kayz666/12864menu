#include "gpio.h"

// 3 通用推挽输出  高速
// 7 通用开漏输出  高速
// B 复用推挽输出
// F 复用开漏输出


// 8 内部上下拉输入
// 0 模拟输入
// 4 浮空输入

void GPIO_Init(void)
{
	RCC->APB2ENR|=1<<2;			//PORTA
	RCC->APB2ENR|=1<<3;    	//PORTB  
	RCC->APB2ENR|=1<<4;			//PORTC
	//RCC->APB2ENR|=1<<5;			//PORTD
	RCC->APB2ENR|=1<<6;    	//PORTE
	//RCC->APB2ENR|=1<<7;    	//PORTF
	//RCC->APB2ENR|=1<<8;    	//PORTG
	
	//配置IO模式
	GPIOA->CRL&=0X0000FF0F;
	GPIOA->CRL|=0X333300B0;

	GPIOA->CRH&=0XFFFF0FF0;
	GPIOA->CRH|=0X00003003;
	
	//GPIOA->ODR|=1<<0;      
	GPIOA->ODR|=1<<4;      
	GPIOA->ODR|=1<<5;      
	GPIOA->ODR|=1<<6;      
	GPIOA->ODR|=1<<7;  
	GPIOA->ODR|=1<<8;      
	GPIOA->ODR|=1<<9;  
	
	
		
	GPIOB->CRL&=0XFF0FFFFF; 
	GPIOB->CRL|=0X00300000;	 
  GPIOB->ODR|=1<<5;      
		
	GPIOB->CRH&=0XFFFFFF0F; 
	GPIOB->CRH|=0X00000030;	 
  GPIOB->ODR|=1<<9;      
	

	GPIOC->CRL&=0X00FFFFFF; 
	GPIOC->CRL|=0X33000000;	 
  GPIOC->ODR|=1<<6;      
	GPIOC->ODR|=1<<7;      
	
	GPIOC->CRH&=0XFFFFFF00; 
	GPIOC->CRH|=0X00000033;  	 
  GPIOC->ODR|=1<<8;      
	GPIOC->ODR|=1<<9; 
	
	GPIOE->CRL&=0XFF00000F;
	GPIOE->CRL|=0X00388880;
	GPIOE->ODR|=1<<1;
	GPIOE->ODR|=1<<2;
	GPIOE->ODR|=1<<3;
	GPIOE->ODR|=1<<4;
	GPIOE->ODR|=1<<5;      
	
	
	//GPIOG->CRH&=0X0FFFFFFF; 
	//GPIOG->CRH|=0X30000000;  	 
  //GPIOG->ODR|=1<<15;      
	
}








