#ifndef __FILEMANAGER_H__
#define __FILEMANAGER_H__
#define STUINFOFILE "student_information.json"
#include"student.h"
#include <stdio.h>

char* getStuInfo();

void writeStuInfo(Student* stu);

#endif