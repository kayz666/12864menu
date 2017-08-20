#include "controlapp.h"

#include "sys.h"
#include "delay.h"
#include "timer.h"
#include "step_motor.h"
#include "hx711.h"


u8 SYSTEM_STATUS=0;
u8 first_flag=1;

struct sysp{
	int MainVel;      // 缓冲器卷绕的速度
	int UnwindingVel;   //退绕的速度
	int FormingVel;     //卷绕系数  主动辊 每转一圈 走动的步数
	int RegressionVel;   //回归速度
	int LengthA;
	int LengthB;
	int TriggerData;   //拉力触发值
  
}SYSTEM_PARAMETER;

void ctrlApp_Init(void)
{
	SYSTEM_PARAMETER.MainVel=100;
	SYSTEM_PARAMETER.UnwindingVel=120;
	SYSTEM_PARAMETER.FormingVel=10;  
	SYSTEM_PARAMETER.RegressionVel=30;
	SYSTEM_PARAMETER.LengthA=0;
	SYSTEM_PARAMETER.LengthB=400;
	SYSTEM_PARAMETER.TriggerData=-1000;
}

void SteeringGearRunToAngle(int angle)
{
	TIM5->CCR2=2000/360*angle+500;
}

void ctrlApp_Main(void)
{
	switch(SYSTEM_STATUS)
	{
		case STOP:
			
			break;
		case RUN_ONE:
			if (first_flag)
			{
				setMotorSpeed(MOTORONE,SYSTEM_PARAMETER.MainVel);
				setMotorSpeed(MOTORTWO,SYSTEM_PARAMETER.MainVel);
				setMotorSpeed(MOTORTHR,SYSTEM_PARAMETER.FormingVel);
			
				setMotorCNT(MOTORTHR,SYSTEM_PARAMETER.LengthB);
				SteeringGearRunToAngle(20);
				
				setMotorEnable(MOTORONE,EN);
				setMotorEnable(MOTORTWO,EN);
				setMotorEnable(MOTORTHR,EN);
				
				first_flag=0;
			}
			if(Pull <SYSTEM_PARAMETER.TriggerData)
			{
				SYSTEM_STATUS=RUN_TWO;
				setMotorSpeed(MOTORTWO,SYSTEM_PARAMETER.MainVel-SYSTEM_PARAMETER.UnwindingVel);
				first_flag=1;
			}
			break;
		case RUN_TWO:
			
			break;
	}
}

void ctrlAppKeyEvent_START(void)
{
	
}

