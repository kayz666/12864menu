#ifndef __HX711_H
#define __HX711_H
#include "sys.h"


#define SCK PBout(0) 
#define DOUT PBin(1)

extern long Pull;
void HX711_Init(int amp, double co);

void set_amp(int amp);
long HX711_is_read(void);
void pulse(void);
unsigned long HX711_read(void);
void HX711_set_offset(long data);
long get_hx711(void);

void HX711_calibration(void);











#endif



