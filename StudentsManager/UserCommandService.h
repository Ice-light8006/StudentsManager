#ifndef __USERCOMMANDSERVICE_H__
#define __USERCOMMANDSERVICE_H__
#include <stdio.h>
#include "Student.h"
#include "List.h"
#include <string.h>

//返回0表示添加失败，返回非0表示添加成功
int addStudent();

void deleteStudent(char* stuID);

#endif