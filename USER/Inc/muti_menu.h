#ifndef __MUTI_MENU_H
#define __MUTI_MENU_H

#include "delay.h"
#include "lcd12864.h"
#include "key.h"

#define u8 unsigned char 
#define u16 unsigned short
#define u32 insigned int
//#define NULL (void*)0
#define SUBMENU_MAXNUM    10  //子菜单最多有多少个
typedef void(*FUNC_POINT)(void);

//定义一个菜单项结构体
typedef struct MenuItem
{
	u8 num;   //本级菜单数量
	u8 recordSubNum;
	char *menuName;
	char *submenuName[SUBMENU_MAXNUM];
	struct MenuItem **submenuPtr;
	struct MenuItem *parent;
	FUNC_POINT func;
	FUNC_POINT funcKeyUP;
	FUNC_POINT funcKeyDOWN;
	FUNC_POINT funcKeyLEFT;
	FUNC_POINT funcKeyRIGHT;
	
}Menu;





void KeyProc(void);
void displayCurrentMenu(void);
void initMenu(void);







#endif



