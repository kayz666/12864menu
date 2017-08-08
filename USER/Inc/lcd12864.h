#ifndef __LCD12864_H
#define __LCD12864_H 

#include "sys.h"
#include "delay.h"

/*LCD 12864*/
#define RS_H PCout(8)=1 //RS=1   4PIN
#define RS_L PCout(8)=0 //RS=0

#define RW_H PCout(7)=1 //RW=1    5PIN
#define RW_L PCout(7)=0  //RW = 0

#define EN_H PCout(6)=1   //EN = 1   6PIN
#define EN_L PCout(6)=0  //EN = 0

#define RESET_L PCout(9)=0
#define RESET_H PCout(9)=1


#define RW_READ PCout(7)

void initLCD12864(void);
void displayString(unsigned char row,unsigned char col,char *ptr);
void clearLcdTxt(void);
void writeWhiteLine(unsigned char line);


#endif

