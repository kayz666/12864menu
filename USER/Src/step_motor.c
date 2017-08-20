#include "step_motor.h"
#include "timer.h"





MOTOR MotorOne={
	IMode,8,CW,0,0,
	110,   
	UN
};
MOTOR MotorTwo={
	IMode,8,CW,0,0,
	110,
	UN
};
MOTOR MotorThr={
	CMode,1,CW,0,0,
	40,
	UN
};

void setMotorOneTimer(void)
{
	TIM3_ChangeTimer(2160000/(MotorOne.fractionize*MotorOne.revlospeed));
	
}
void setMotorTwoTimer(void)
{
	TIM4_ChangeTimer(2160000/(MotorTwo.fractionize*MotorTwo.revlospeed));
	
}
void setMotorThrTimer(void)
{
	TIM2_ChangeTimer(2160000/(MotorThr.fractionize*MotorThr.revlospeed));
	
}
void motorCalculation(void)
{
	//TIM3_ChangeTimer(720);
	setMotorOneTimer();
	setMotorTwoTimer();
	setMotorThrTimer();
}

void motor_init(void)
{
	motorCalculation();
	//TIM3_ChangeTimer(5000);
	//TIM4_ChangeTimer(5000);
	//TIM3_Enable();
	//TIM4_Enable();
}

void motor_changeEnable(void)
{
		MotorOne.enable=!MotorOne.enable;
		MotorTwo.enable=!MotorTwo.enable;
		if(MotorOne.enable == EN) 
		{
			MotorOne.step=0;
			TIM3_Enable();
		}
		else 
		{
			TIM3_Disenable();
			
		}
		if(MotorTwo.enable == EN) 
		{
			MotorTwo.step=0;
			TIM4_Enable();
		}
		else 
		{
			TIM4_Disenable();
			
		}
}

void setMotorEnable(u8 MotorNum,u8 data)
{
	if (MotorNum == MOTORONE)
	{
		if( data == EN)
		{
			if(MotorOne.enable != EN)
			{
				MotorOne.enable=EN;
				TIM3_Enable();
			}
		}else
		{
			if(MotorOne.enable != UN)
			{
				MotorOne.enable=UN;
				TIM3_Disenable();
			}
		}
	}else if(MotorNum == MOTORTWO)
	{
		if( data == EN)
		{
			if(MotorTwo.enable != EN)
			{
				MotorTwo.enable=EN;
				TIM4_Enable();
			}
		}else
		{
			if(MotorTwo.enable != UN)
			{
				MotorTwo.enable=UN;
				TIM4_Disenable();
			}
		}
	}
	else if(MotorNum == MOTORTHR)
	{
		if( data == EN)
		{
			if(MotorThr.enable != EN)
			{
				MotorThr.enable=EN;
				TIM2_Enable();
			}
		}else
		{
			if(MotorThr.enable != UN)
			{
				MotorThr.enable=UN;
				TIM2_Disenable();
			}
		}		
	}
}
void setMotorCNT(u8 MotorNum,int cnt)
{
		if (MotorNum == MOTORONE)
	{
		
	}else if(MotorNum == MOTORTWO)
	{
		
	}
	else if(MotorNum == MOTORTHR)
	{
		if (cnt >=0)
		{
			MotorThr.clkcnt=cnt;
			MotorThr.dir=CW;
			MOTOR_THR_CWH;
		}
		else
		{
			MotorThr.clkcnt=0-cnt;
			MotorThr.dir=CCW;
			MOTOR_THR_CWL;
		}
	}
}

void setMotorSpeed(u8 MotorNum,int vel)
{
	if (MotorNum == MOTORONE)
	{
		if(vel>=0)
		{
			if(vel != MotorOne.revlospeed)
			{
				MOTOR_ONE_CWPIN=CW;
				MotorOne.dir=CW;
				MotorOne.revlospeed=vel;
				setMotorOneTimer();
			}
		}
		else
		{
			if((0-vel) != MotorOne.revlospeed)
			{
				MOTOR_ONE_CWPIN=CCW;
				MotorOne.dir=CCW;
				MotorOne.revlospeed=0-vel;
				setMotorOneTimer();
			}
		}
			
	}else if(MotorNum == MOTORTWO)
	{
		if(vel>=0)
		{
			if(vel != MotorTwo.revlospeed)
			{
				MOTOR_TWO_CWPIN=CW;
				MotorTwo.dir=CW;
				MotorTwo.revlospeed=vel;
				setMotorTwoTimer();
			}
		}
		else
		{
			if((0-vel) != MotorTwo.revlospeed)
			{
				MOTOR_TWO_CWPIN=CCW;
				MotorTwo.dir=CCW;
				MotorTwo.revlospeed=0-vel;
				setMotorTwoTimer();
			}
		}
	}
	else if(MotorNum == MOTORTHR)
	{
		MotorThr.revlospeed=vel;
		setMotorThrTimer();
	}
}


void motorOne_TimerEvent(void)
{
	if (MotorOne.mode == IMode)
	{
		if(MotorOne.dir == CW) MOTOR_ONE_CWH;
		else MOTOR_ONE_CWL;
		MOTOR_ONE_CLKT;
		MotorOne.step++;
	}else
	{
			if(MotorOne.clkcnt > 0)
			{
				MOTOR_ONE_CLKT;
				MotorOne.clkcnt--;
			}
	}

}
void motorTwo_TimerEvent(void)
{
		if (MotorTwo.mode == IMode)
	{
		if(MotorTwo.dir == CW) MOTOR_TWO_CWH;
		else MOTOR_TWO_CWL;
		MOTOR_TWO_CLKT;
		MotorTwo.step++;
	}else
	{
			if(MotorTwo.clkcnt > 0)
			{
				MOTOR_TWO_CLKT;
				MotorTwo.clkcnt--;
			}
	}
}

void motorThr_TimerEvent(void)
{
		if (MotorThr.mode == IMode)
	{
		if(MotorThr.dir == CW) MOTOR_THR_CWH;
		else MOTOR_THR_CWL;
		MOTOR_THR_CLKT;
		MotorThr.step++;
	}else
	{
			if(MotorThr.dir == CW) MOTOR_THR_CWH;
			else MOTOR_THR_CWL;
			if(MotorThr.clkcnt > 0)
			{
				MOTOR_THR_CLKT;
				MotorThr.clkcnt--;
			}
	}
}





















