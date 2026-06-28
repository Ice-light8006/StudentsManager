#ifndef __QUERYMENU_H__
#define __QUERYMENU_H__
#include <stdio.h>
#include "list.h"
#include <stdlib.h>


enum operateFlag
{
	QUERYNAME = 1,
	QUERYBIRTHYEAR = 2,
	QUERYENROLLMENT = 3,
	QUERYALL = 4,
	QUERYEXIT = 0
};

void showQueryMenu();

void choseQueryOperate();

#endif