#ifndef __USERCOMMANDSERVICE_H__
#define __USERCOMMANDSERVICE_H__
#include <stdio.h>
#include "Student.h"
#include "List.h"
#include <string.h>
#include <stdlib.h>
#include "Utils.h"
#include "QueryMenu.h"
#include "Display.h"

//返回0表示添加失败，返回非0表示添加成功
int addStudent(Node* pHead);

//返回0表示删除失败，返回1表示删除成功
int deleteStudent(Node* pHead);

#endif