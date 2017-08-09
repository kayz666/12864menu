#include "muti_menu.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

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
		"菜单1",
		"菜单2",
		"菜单3",
		"菜单4",
		"菜单5",
		"菜单6",
		"菜单7",
		"菜单8"
	}
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

struct currMenu
{
	Menu *menu;   			//指向的菜单指针
	//u8 selectRow;      //当前选择的是哪一项
	
	
}CurrMenu;


void keyEvent_menuUP(void);
void keyEvent_menuDOWN(void);
void keyEvent_menuENTER(void);
void keyEvent_menuBACK(void);
void keyEvent_Empty(void);
void GUIfunc_showTest(void);
void GUIfunc_setRunningData(void);
void GUIfunc_showData(void);

void initMenu(void)
{
	u8 i;
	Menu_main.submenuPtr=malloc(sizeof(&Menu_main)*Menu_main.num);
	Menu_main.submenuPtr[0]=&Interface_showData;
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
	for(i=0;i<Menu_more.num;i++) Menu_more.submenuPtr[i]=&Interface_showTest;
	Menu_more.parent=&Menu_main;
	Menu_more.funcKeyUP=&keyEvent_menuUP;
	Menu_more.funcKeyDOWN=&keyEvent_menuDOWN;
	Menu_more.funcKeyLEFT=&keyEvent_menuBACK;
	Menu_more.funcKeyRIGHT=&keyEvent_menuENTER;
	
	Interface_showData.func=&GUIfunc_showData;
	Interface_showData.parent=&Menu_main;
	Interface_showData.funcKeyUP=&keyEvent_Empty;
	Interface_showData.funcKeyDOWN=&keyEvent_Empty;
	Interface_showData.funcKeyLEFT=&keyEvent_menuBACK;
	Interface_showData.funcKeyRIGHT=&keyEvent_Empty;
	
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
		printf("%d",CurrMenu.menu->recordSubNum);
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

void GUIfunc_showTest(void)
{
	displayString(0,0,"测试  ");
	displayString(1,0,"                ");
	displayString(2,0,"        ");
	displayString(3,0,"返回        确认");
}
void GUIfunc_showData(void)
{
	displayString(0,0,"主速度=   ");
	displayString(1,0,"转速=");
	displayString(2,0,"        ");
	displayString(3,0,"        ");
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
	if (CurrMenu.menu->recordSubNum<(CurrMenu.menu->num-1))
	{
		CurrMenu.menu->recordSubNum++;
		//CurrMenu.menu->recordSubNum=CurrMenu.selectRow;
	}
}

void keyEvent_menuDOWN(void)
{
	if (CurrMenu.menu->recordSubNum>0)
	{
		CurrMenu.menu->recordSubNum--;
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


















