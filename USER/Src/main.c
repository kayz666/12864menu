#include "sys.h"
#include "delay.h"
#include "gpio.h"
#include "lcd12864.h"
#include "stdio.h"
#include "key.h"
#include "usart.h"
#include "muti_menu.h"
#include "timer.h"




int main(void)
{	
	
	u8 i=0;
	Stm32_Clock_Init(9);
	delay_init(72);	    //延时函数初始化	  
	GPIO_Init();
	TIM3_Int_Init(4999,7199);  //5000-1   500ms
	uart_init(72,115200);
	initLCD12864();
	delay_ms(100);
	initMenu();
	while(1)
	{
		keyRead();
		KeyProc();
		i>10?i=0:i++;
		if (i==10)
		{
			displayCurrentMenu();
			//LED0_T;
		}
		
		delay_ms(10);
	}
}
 
//void show(void)
//{
//	char s[18]={0};
//	sprintf(s,"速度=%dHH  %d   ",icnt,Trg);
//	displayString(0,0,"我的同学  \x10");
//	displayString(1,0,"叫哈哈11  \x10");
//	displayString(2,0,"叫哈哈12  \x10");
//	displayString(3,0,s);
//	writeWhiteLine(4);
//	LED0_T;
//	printf("%d",icnt);
//}





