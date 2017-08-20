#include "sys.h"
#include "delay.h"
#include "gpio.h"
#include "lcd12864.h"
#include "stdio.h"
#include "key.h"
#include "usart.h"
#include "muti_menu.h"
#include "timer.h"
#include "step_motor.h"
#include "hx711.h"
#include "controlapp.h"


int main(void)
{	
	
	u8 i=0;
	Stm32_Clock_Init(9);
	delay_init(72);	    //延时函数初始化	  
	GPIO_Init();
	
	TIM2_Init(); 
	TIM3_Init(); 
	TIM4_Init(); 
	TIM5_PWM_Init(19999,71);
	uart_init(72,115200);
	initLCD12864();
	HX711_Init(128,1);
	ctrlApp_Init();
	initMenu();
	motor_init();
	HX711_calibration();
	while(1)
	{
		unsigned long temp=0;
		keyRead();
		KeyProc();
		i>100?i=0:i++;
		if (i==100)
		{
			displayCurrentMenu();
			LED0_T;
			//TIM5->CCR2=psc;
			//temp=HX711_read();
			//Pull=temp/100-84074;
		}
		ctrlApp_Main();

		delay_ms(1);
	}
}
 





