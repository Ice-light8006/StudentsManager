#ifndef __MAINMENU_H__
#define __MAINMENU_H__
#include <stdio.h>
#include <stdlib.h>

enum Operate
{
	EXIT = 0,
	QUERY = 1,
	ADD = 2,
	DELETE = 3
};

void showMainMenu();

void choseOperate();

#endif