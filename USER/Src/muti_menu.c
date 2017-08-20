#include "muti_menu.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "step_motor.h"
#include "timer.h"
#include "hx711.h"

Menu Menu_main={
	3,0,
	"    主菜单",
	{
		"显示",
		"设置",
		"更多"
	}
};

Menu Menu_set={
	2, 0,
	"    设置",
	{
		"运行参数",
		"参数2"
	}
};

Menu Menu_more={
	8,0,
	"    更多",
	{
		"显示测试1",
		"微型滑台测试",
		"菜单3",
		"菜单4",
		"菜单5",
		"菜单6",
		"菜单7",
		"菜单8"
	}
};

Menu Interface_huataiTest={
	0,0
};
	
Menu Interface_showData={
	0,0
};
Menu Interface_setRunningData={
	0,0
};
Menu Interface_showTest={
	0,0
};
Menu Interface_microStepMotorTest={
	0,0
};

Menu SetupMenu_setStepOne={
	-1,0,
	"    设置",
	{
		"MotorOne.Rev"
		"MotorOne.Dir"
	}
};

struct
{
	Menu *menu;   			//指向的菜单指针
	//u8 selectRow;      //当前选择的是哪一项
	
	
}CurrMenu;

char StringTemp[17]={0};




void keyEvent_menuUP(void);
void keyEvent_menuDOWN(void);
void keyEvent_menuENTER(void);
void keyEvent_menuBACK(void);
void keyEvent_Empty(void);
void GUIfunc_showTest(void);
void GUIfunc_setRunningData(void);
void GUIfunc_showData(void);
void GUIfunc_microStepMotorTest(void);
void keyEvent_microStepUP(void);
void keyEvent_microStepDOWN(void);

void initMenu(void)
{
	u8 i;
	Menu_main.submenuPtr=malloc(sizeof(&Menu_main)*Menu_main.num);
	//for(i=0;i<
	Menu_main.submenuPtr[0]=NULL;
	Menu_main.submenuPtr[1]=&Menu_set;
	Menu_main.submenuPtr[2]=&Menu_more;
	Menu_main.parent=NULL;
	Menu_main.funcKeyUP=&keyEvent_menuUP;
	Menu_main.funcKeyDOWN=&keyEvent_menuDOWN;
	Menu_main.funcKeyLEFT=&keyEvent_Empty;
	Menu_main.funcKeyRIGHT=&keyEvent_menuENTER;
	
	Menu_set.submenuPtr=malloc(sizeof(&Menu_set)*Menu_set.num);
	Menu_set.submenuPtr[0]=&Interface_setRunningData;
	Menu_set.submenuPtr[1]=&Interface_showTest;
	Menu_set.parent=&Menu_main;
	Menu_set.funcKeyUP=&keyEvent_menuUP;
	Menu_set.funcKeyDOWN=&keyEvent_menuDOWN;
	Menu_set.funcKeyLEFT=&keyEvent_menuBACK;
	Menu_set.funcKeyRIGHT=&keyEvent_menuENTER;
	
	
	Menu_more.submenuPtr=malloc(sizeof(&Menu_more)*Menu_more.num);
	Menu_more.submenuPtr[0]=&Interface_showData;
	Menu_more.submenuPtr[1]=&Interface_microStepMotorTest;
	Menu_more.submenuPtr[2]=&Interface_showTest;
	Menu_more.submenuPtr[3]=&Interface_showTest;
	Menu_more.submenuPtr[4]=&Interface_showTest;
	Menu_more.submenuPtr[5]=&Interface_showTest;
	Menu_more.submenuPtr[6]=&Interface_showTest;
	Menu_more.submenuPtr[7]=&Interface_showTest;
	Menu_more.parent=&Menu_main;
	Menu_more.funcKeyUP=&keyEvent_menuUP;
	Menu_more.funcKeyDOWN=&keyEvent_menuDOWN;
	Menu_more.funcKeyLEFT=&keyEvent_menuBACK;
	Menu_more.funcKeyRIGHT=&keyEvent_menuENTER;
	
	Interface_showData.func=&GUIfunc_showData;
	Interface_showData.parent=&Menu_more;
	Interface_showData.funcKeyUP=&keyEvent_Empty;
	Interface_showData.funcKeyDOWN=&keyEvent_Empty;
	Interface_showData.funcKeyLEFT=&keyEvent_menuBACK;
	Interface_showData.funcKeyRIGHT=&motor_changeEnable;
	
	Interface_setRunningData.func=&GUIfunc_setRunningData;
	Interface_setRunningData.parent=&Menu_set;
	Interface_setRunningData.funcKeyUP=&keyEvent_Empty;
	Interface_setRunningData.funcKeyDOWN=&keyEvent_Empty;
	Interface_setRunningData.funcKeyLEFT=&keyEvent_menuBACK;
	Interface_setRunningData.funcKeyRIGHT=&keyEvent_Empty;
	
	Interface_showTest.func=&GUIfunc_showTest;
	Interface_showTest.parent=&Menu_more;
	Interface_showTest.funcKeyUP=&keyEvent_Empty;
	Interface_showTest.funcKeyDOWN=&keyEvent_Empty;
	Interface_showTest.funcKeyLEFT=&keyEvent_menuBACK;
	Interface_showTest.funcKeyRIGHT=&keyEvent_Empty;
	
	Interface_microStepMotorTest.func=&GUIfunc_microStepMotorTest;
	Interface_microStepMotorTest.parent=&Menu_more;
	Interface_microStepMotorTest.funcKeyUP=&keyEvent_microStepUP;
	Interface_microStepMotorTest.funcKeyDOWN=&keyEvent_microStepDOWN;
	Interface_microStepMotorTest.funcKeyLEFT=&keyEvent_menuBACK;
	Interface_microStepMotorTest.funcKeyRIGHT=&keyEvent_Empty;
	
	
	CurrMenu.menu=&Menu_main;
	//CurrMenu.selectRow=0;
	
	
	
}


void displayCurrentMenu(void)
{
	u8 i,j;
	u8 page;
	char tempstr[16]={0};
	if (CurrMenu.menu->num > 0)
	{
		displayString(0,0,CurrMenu.menu->menuName);
		CurrMenu.menu->recordSubNum<3?(page=1):(page=CurrMenu.menu->recordSubNum/3+1);
		//printf("%d",CurrMenu.menu->recordSubNum);
		for(i=0;i<3;i++)
		{
			j=(page-1)*3+i;
			if (j<CurrMenu.menu->num)
			{
				sprintf(tempstr,"%d",j+1);
				displayString(i+1,0,tempstr);
				displayString(i+1,1,CurrMenu.menu->submenuName[j]);
				if ((CurrMenu.menu->submenuPtr[j])->num != 0) displayString(i+1,7,"\x10");
			}else
			{
				displayString(i+1,0,"        ");
			}
		}
		writeWhiteLine(CurrMenu.menu->recordSubNum%3+2);
	}
	else
	{
		CurrMenu.menu->func();
	}
}

void keyEvent_microStepUP(void)
{
	MotorThr.dir=CCW;
	MotorThr.clkcnt=400;
	//motor_changeEnable();
	
}
void keyEvent_microStepDOWN(void)
{
	MotorThr.dir=CW;
	MotorThr.clkcnt=400;
}


void GUIfunc_microStepMotorTest(void)
{
	displayString(0,0,"微型步进电机测试");
	displayString(1,0,"停止");
	displayString(2,0,"");
	displayString(3,0,"返回        确认");
	MotorThr.enable=EN;
	TIM2_Enable(); 
}

void GUIfunc_showTest(void)
{
	displayString(0,0,"测试  ");
	sprintf(StringTemp,"%d        ",get_hx711());
	displayString(1,0,StringTemp);
	displayString(2,0,"        ");
	displayString(3,0,"返回        确认");
}
void GUIfunc_showData(void)
{
	
	displayString(0,0,"    实时显示");
	sprintf(StringTemp,"方向：%d",MotorOne.dir);
	displayString(3,0,StringTemp);
	sprintf(StringTemp,"转速：%d    ",MotorOne.revlospeed);
	displayString(2,0,StringTemp);
	sprintf(StringTemp,"步数：%d      ",MotorOne.step);
	displayString(1,0,StringTemp);
	if (MotorOne.enable == EN) sprintf(StringTemp,"运行");
	else sprintf(StringTemp,"停止");
	displayString(3,6,StringTemp);
}

void GUIfunc_setRunningData(void)
{
	displayString(0,0,"设置选项");
	displayString(1,0,"最大转速");
	displayString(2,0,"是否启用自动控制");
	displayString(3,0,"        ");
}

void keyEvent_menuUP(void)
{
	if (CurrMenu.menu->recordSubNum>0)
	{
		CurrMenu.menu->recordSubNum--;
		//CurrMenu.menu->recordSubNum=CurrMenu.selectRow;
	}

}

void keyEvent_menuDOWN(void)
{
	if (CurrMenu.menu->recordSubNum<(CurrMenu.menu->num-1))
	{
		CurrMenu.menu->recordSubNum++;
		//CurrMenu.menu->recordSubNum=CurrMenu.selectRow;
	}
}

void keyEvent_menuENTER(void)
{
	clearLcd();
	CurrMenu.menu=CurrMenu.menu->submenuPtr[CurrMenu.menu->recordSubNum];
	CurrMenu.menu->recordSubNum=0;
}

void keyEvent_menuBACK(void)
{
	
	if (CurrMenu.menu->parent != NULL)
	{
		clearLcd();
		CurrMenu.menu=CurrMenu.menu->parent;
	}
}

void keyEvent_Empty(void){}


void KeyProc(void)
{

	
	if (Trg>0)
	{
		if(Trg&(1<<UP_Press))
		{
			CurrMenu.menu->funcKeyUP();
		}
		else if(Trg&(1<<DOWN_Press))
		{
			CurrMenu.menu->funcKeyDOWN();
		}
		else if(Trg&(1<<LEFT_Press))
		{
			CurrMenu.menu->funcKeyLEFT();
		}
		else if(Trg&(1<<RIGHT_Press))
		{
			CurrMenu.menu->funcKeyRIGHT();
		}
	}
	
}


















