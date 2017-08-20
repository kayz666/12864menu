#ifndef __STEP_MOTOR_H
#define __STEP_MOTOR_H

#include "sys.h"


#define MOTOR_ONE_CLKPIN PAout(5)
#define MOTOR_ONE_CWPIN PAout(4)

#define MOTOR_TWO_CLKPIN PAout(7)
#define MOTOR_TWO_CWPIN PAout(6)

#define MOTOR_THR_CLKPIN PAout(8)
#define MOTOR_THR_CWPIN PAout(11)


#define MOTOR_ONE_CLKH MOTOR_ONE_CLKPIN=1
#define MOTOR_ONE_CLKL MOTOR_ONE_CLKPIN=0
#define MOTOR_ONE_CLKT MOTOR_ONE_CLKPIN=!MOTOR_ONE_CLKPIN
#define MOTOR_ONE_CWH MOTOR_ONE_CWPIN=1
#define MOTOR_ONE_CWL MOTOR_ONE_CWPIN=0

#define MOTOR_TWO_CLKH MOTOR_TWO_CLKPIN=1
#define MOTOR_TWO_CLKL MOTOR_TWO_CLKPIN=0
#define MOTOR_TWO_CLKT MOTOR_TWO_CLKPIN=!MOTOR_TWO_CLKPIN
#define MOTOR_TWO_CWH MOTOR_TWO_CWPIN=1
#define MOTOR_TWO_CWL MOTOR_TWO_CWPIN=0

#define MOTOR_THR_CLKH MOTOR_THR_CLKPIN=1
#define MOTOR_THR_CLKL MOTOR_THR_CLKPIN=0
#define MOTOR_THR_CLKT MOTOR_THR_CLKPIN=!MOTOR_THR_CLKPIN
#define MOTOR_THR_CWH MOTOR_THR_CWPIN=1
#define MOTOR_THR_CWL MOTOR_THR_CWPIN=0


#define MOTORONE 1
#define MOTORTWO 2
#define MOTORTHR 3

#define CW   1   //顺时针
#define CCW  0   //逆时针
#define CMode   1   //计数模式 count mode 
#define IMode  0   //无限模式 infinite mode
#define EN  1
#define UN  0


typedef struct{
	u8 mode;					//模式
	u8 fractionize;  //细分
	u8 dir;						//方向
	u32 clkcnt;			//脉冲个数
	u32 step;				//步数计数
	u16 revlospeed;  //转速
	u8 enable;     //使能
}MOTOR;

extern MOTOR MotorOne;
extern MOTOR MotorTwo;
extern MOTOR MotorThr;

void motor_init(void);
void motorOne_TimerEvent(void);
void motorTwo_TimerEvent(void);
void motorThr_TimerEvent(void);
void motor_changeEnable(void);

void setMotorSpeed(u8 MotorNum,int vel);
void setMotorEnable(u8 MotorNum,u8 data);
void setMotorCNT(u8 MotorNum,int cnt);

#endif

