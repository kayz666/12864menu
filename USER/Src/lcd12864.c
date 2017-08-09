#include "lcd12864.h"

unsigned char whiteLine=0;

unsigned char TABLE[]={
	0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,
	0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,
	0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,        
	0x98,0x99,0x9a,0x9b,0x9c,0x9d,0x9e,0x9f};

//串行模式 发送一字节数据
void sendByte(unsigned char data)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		EN_L;
		if(data&0x80)RW_H;
		else RW_L;
		delay_us(2);
		EN_H;
		data=data<<1;
		delay_us(2);
	}
}

//写控制命令
void sendCMD(unsigned char cmd)
{
	RS_H;
	//delay_us(100);
	sendByte(0xF8);
	sendByte(cmd&0xF0);
	sendByte((cmd&0x0F)<<4);
	RS_L;
	//delay_us(100);
}

//写数据命令
void sendData(unsigned char data)
{
	RS_H;
	//delay_us(100);
	sendByte(0xFA);
	sendByte(data&0xF0);
	sendByte((data&0x0F)<<4);
	RS_L;
	//delay_us(100);
}

//从LCD接收一个数据
unsigned char receiveByte(void)
{
	unsigned char i,temp1=0,temp2=0;
	for(i=0;i<8;i++)
	{
		temp1=temp1<<1;
		EN_L;
		delay_us(10);
		EN_H;
		delay_us(10);
		EN_L;
		if(RW_READ)temp1++;
	}
	for(i=0;i<8;i++)
	{
		temp2=temp2<<1;
		EN_L;
		delay_us(10);
		EN_H;
		delay_us(10);
		EN_L;
		if(RW_READ)temp2++;
	}
	return ((temp1&0xF0)+(temp2&0x0F));
}
	
//检查忙标志
void checkBusy(void)
{
	do sendByte(0xFC);
	while(0x80&receiveByte());
}



//显示一个字符串到指定位置
void displayString(unsigned char row,unsigned char col,char *ptr)
{
	sendCMD(TABLE[8*row+col]);
	while(*ptr != '\0')
	{
		sendData(*ptr++);
	}
}
//反白之前先清绘图存储区
void dispBlack(void)
{
	unsigned char i,j;
	sendCMD(0x34);
	for(i=0;i<32;i++)
	{
		//checkBusy();
		sendCMD(0x80+i);
		sendCMD(0x80);
		for(j=0;j<16;j++) sendData(0x00);
	}
	for(i=0;i<32;i++)
	{
		sendCMD(0x80+i);
		sendCMD(0x88);
		for(j=0;j<16;j++) sendData(0x00);
	}
	sendCMD(0x34);
}

//反白第Y行的第X个到end_x个字符  
void writeWhite(unsigned char CX,unsigned char CY,unsigned char width,unsigned char YN,unsigned char f)
{
	unsigned char halfLineCnt,basicBlock,lcdPosX,lcdPosY;
	if (f==1)dispBlack();
	lcdPosY=0x80;
	if (CX == 0)
	{
		CX=0x80;
		halfLineCnt=16;
	}
	else if (CX ==1)
	{
		CX=0x80;
		halfLineCnt =32;
	}
	else if (CX ==2)
	{
		CX=0x88;
		halfLineCnt =16;
	}
	else if (CX == 3)
	{
		CX=0x88;
		halfLineCnt =32;
	}
	lcdPosX=CX+CY;
	for(;halfLineCnt !=0;halfLineCnt--)
	{
		basicBlock=width;
		sendCMD(0x34);
		sendCMD(lcdPosY);
		sendCMD(lcdPosX);
		sendCMD(0x30);
		for(;basicBlock !=0;basicBlock--)
		{
			if(halfLineCnt>16)
			{
				sendData(0x00);
			}
			else
			{
				if(YN==1)sendData(0xFF);
				else sendData(0x00);
			}
		}
		lcdPosY++;
	}
	sendCMD(0X36);
	sendCMD(0x30);
}


//反白显示第x行
void writeWhiteLine(unsigned char line)
{
	if(line==0)
	{
		if (line != whiteLine)
		{
			writeWhite(whiteLine,0,16,0,1);
			whiteLine = line;
		}
	}else
	{
		if (line != whiteLine)
		{
			writeWhite(line-1,0,16,1,1);
			whiteLine = line;
		}
	}
}

void clearLcd(void)
{
	clearLcdTxt();
	writeWhiteLine(0);
}
//清屏txt
void clearLcdTxt(void)
{
	unsigned char i;
	sendCMD(0x30);
	sendCMD(0x80);
	for(i=0;i<64;i++)sendData(0x20);

}
//清屏BMP
void clearLcdBMP(void)
{
	unsigned char i,j;
	sendCMD(0x34);
	sendCMD(0x36);
	for(i=0;i<32;i++)
	{
		sendCMD(0x80|i);
		sendCMD(0x80);
		for(j=0;j<32;j++)sendData(0x00);
	}
}

void initLCD12864(void)
{
	RS_L;
	RESET_L;
	delay_ms(100);
	RESET_H;
	delay_ms(20);
	sendCMD(0x30);
	sendCMD(0x0C);
	sendCMD(0x01);
	sendCMD(0x02);
	sendCMD(0x80);
}









