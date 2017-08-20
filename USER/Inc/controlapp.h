#ifndef __CONTROLAPP_H
#define __CONTROLAPP_H

#define STOP 0
#define RUN_ONE 1
#define RUN_TWO 2

extern struct sysp SYSTEM_PARAMETER;


void ctrlApp_Init(void);
void ctrlApp_Main(void);
void ctrlAppKeyEvent_START(void);
#endif


