#include <hx711.h>
#include<delay.h>

long OFFSET;
long Pull;

void HX711_Init(int amp,double co)
{
	
	RCC->APB2ENR|=1<<3;  //PORTB 
	GPIOB->CRL&=0xFFFFFF00;
	GPIOB->CRL|=0x00000083; // PB0=SCK  ‰≥ˆ  PB1=DOUT ‰»Î
  SCK=0;
}



//long HX711_read()
//{
//	int i;
//	long val=0;
//	SCK=0;
//	
//	
//	while(DOUT==0);
//	for(i=0;i<24;i++)
//	{
//		pulse();
//		val<<=1;
//		if(DOUT==1)val++;
//		
//	}
//	for(i=0;i<AMP;i++)
//	{
//		pulse();
//	}
//	return val& (1L << 23) ? val | ((-1L) << 24) : val;

//	
//}
unsigned long HX711_read(void)
{
	unsigned long count=0;
	unsigned char i;
	SCK=0;
	while(DOUT);
	for (i=0;i<24;i++)
	{
		SCK=1;
		count=count<<1;
		SCK=0;
		if(DOUT)count++;
	}
	SCK=1;
	count=count^0x800000;
	SCK=0;
	return count;
}

long get_hx711(void)
{
	unsigned long temp;
	temp=HX711_read();
	Pull=temp/100-OFFSET;
	return Pull;
}

void HX711_calibration(void)
{
	u8 i=0;
	long temp=0;
	for(i=0;i<10;i++)
	{
		temp=temp+HX711_read();
		delay_us(500);
	}
	HX711_set_offset(temp/1000);
}
void pulse()
{
	SCK=1;
	delay_us(3);
	SCK=0;
	delay_us(3);
}

void HX711_set_offset(long data)
{
	OFFSET=data;
}



