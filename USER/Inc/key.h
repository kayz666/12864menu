#ifndef __KEY_H
#define __KEY_H

#include "sys.h"

#define UP_Press 0
#define DOWN_Press 1
#define LEFT_Press 2
#define RIGHT_Press 3

extern u8 Trg;
extern u8 Cont;

void keyRead(void);

#endif



