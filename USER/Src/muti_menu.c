#include "muti_menu.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

Menu MainMenu={
	3,
	"    主菜单",
	{
		"显示",
		"设置",
		"更多"
	}
};

Menu SetMenu={
	2, 
	"    设置",
	{
		"运行参数",
		"参数2"
	}
};

Menu MoreMenu={
	8,
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
	

struct currMenu
{
	Menu *menu;   			//指向的菜单指针
	u8 selectRow;      //当前选择的是哪一项
	
	
}CurrMenu;

void showfunc(void);
void keyEvent_SelectUP(void);
void keyEvent_SelectDOWN(void);
void keyEvent_SelectENTER(void);
void keyEvent_SelectBACK(void);

void initMenu(void)
{
	u8 i;
	MainMenu.submenuPtr=malloc(sizeof(&MainMenu)*MainMenu.num);
	MainMenu.submenuPtr[0]=NULL;
	MainMenu.submenuPtr[1]=&SetMenu;
	MainMenu.submenuPtr[2]=&MoreMenu;
	MainMenu.func=malloc(sizeof(FUNC_POINT)*MainMenu.num);
	MainMenu.func[0]=&showfunc;
	MainMenu.parent=NULL;
	MainMenu.funcKeyUP=&keyEvent_SelectUP;
	
	MoreMenu.submenuPtr=malloc(sizeof(&MoreMenu)*MoreMenu.num);
	MoreMenu.func=malloc(sizeof(FUNC_POINT)*MoreMenu.num);
	for(i=0;i<MoreMenu.num;i++) MoreMenu.submenuPtr[i]=NULL;
	for(i=0;i<MoreMenu.num;i++) MoreMenu.func[i]=NULL;
	MoreMenu.funcKeyUP=&keyEvent_SelectUP;
	MoreMenu.funcKeyDOWN=&keyEvent_SelectDOWN;
	
	
	
	CurrMenu.menu=&MainMenu;
	CurrMenu.selectRow=0;
	
	
	
	
	
}


void displayCurrentMenu(void)
{
	u8 i,j;
	u8 page;
	char tempstr[16]={0};
	if (CurrMenu.menu->num > 0)
	{
		displayString(0,0,CurrMenu.menu->menuName);
		CurrMenu.selectRow<3?(page=1):(page=CurrMenu.selectRow/3+1);
		printf("%d",CurrMenu.selectRow);
		for(i=0;i<3;i++)
		{
			j=(page-1)*3+i;
			if (j<CurrMenu.menu->num)
			{
				sprintf(tempstr,"%d",j+1);
				displayString(i+1,0,tempstr);
				displayString(i+1,1,CurrMenu.menu->submenuName[j]);
				if ((CurrMenu.menu->submenuPtr[j]) != NULL) displayString(i+1,7,"\x10");
			}else
			{
				displayString(i+1,0,"        ");
			}
		}
		writeWhiteLine(CurrMenu.selectRow%3+2);
	}
}



void showfunc(void)
{
	
}


void keyEvent_SelectUP(void)
{
	if (CurrMenu.selectRow<(CurrMenu.menu->num-1))
	{
		CurrMenu.selectRow++;
	}
}

void keyEvent_SelectDOWN(void)
{
	if (CurrMenu.selectRow>0) CurrMenu.selectRow--;
}

void keyEvent_SelectENTER(void)
{
	
}

void keyEvent_SelectBACK(void)
{
	
}

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


















