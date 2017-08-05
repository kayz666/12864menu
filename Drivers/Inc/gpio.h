#ifndef __GPIO_H
#define __GPIO_H 

#include "sys.h"

#define LED0 PBout(5)	// DS0
#define LED1 PEout(5)	// DS1	

#define LED0_H LED0=1
#define LED0_L LED0=0
#define LED0_T LED0=!LED0
#define LED1_H LED1=1
#define LED1_L LED1=0
#define LED1_T LED1=!LED1


void GPIO_Init(void);
	


#endif

