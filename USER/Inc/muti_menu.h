#ifndef __MUTI_MENU_H
#define __MUTI_MENU_H

#include "delay.h"
#include "lcd12864.h"
#include "key.h"

#define u8 unsigned char 
#define u16 unsigned short
#define u32 unsigned int
	
//#define NULL (void*)0
#define SUBMENU_MAXNUM    10  //子菜单最多有多少个
typedef void(*FUNC_POINT)(void);

//定义一个菜单项结构体
typedef struct MenuItem
{
	int num;  //菜单数量   对应显示的模式  
						//大于0表示正常菜单  
						//0  特殊的一个菜单 表示显示的用户界面，有自己独立的按键触发函数 
						//小于0 固定格式的设置界面  可以快速更改自己需要改变的参数
	u8 recordSubNum;  //记录选择菜单项的值
	char *menuName;   //菜单名称
	char *submenuName[SUBMENU_MAXNUM];   //菜单项对应的名字
	struct MenuItem **submenuPtr;        //菜单项指向的菜单的指针地址 
	struct MenuItem *parent;        //父菜单的指针
	FUNC_POINT func;                // 用户界面对应的 界面GUI函数
	FUNC_POINT funcKeyUP;   				
	FUNC_POINT funcKeyDOWN;
	FUNC_POINT funcKeyLEFT;
	FUNC_POINT funcKeyRIGHT;
	
}Menu;





void KeyProc(void);
void displayCurrentMenu(void);
void initMenu(void);







#endif



