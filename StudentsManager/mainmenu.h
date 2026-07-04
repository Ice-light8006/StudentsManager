#ifndef __MAINMENU_H__
#define __MAINMENU_H__
#include <stdio.h>
#include <stdlib.h>

enum Operate
{
	EXIT = 0,
	QUERY = 4,
	ADD = 1,
	DELETE = 2,
	PICK = 5,
	MODIFY = 3

};

void showMainMenu();

void choseOperate();

#endif