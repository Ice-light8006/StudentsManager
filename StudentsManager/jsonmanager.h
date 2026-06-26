#ifndef __JSONMANAGER_H__
#define __JSONMANAGER_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"
#include "list.h"

// ---------- 公开函数声明 ----------
// 解析 JSON 对象字符串 → Student 结构体
void parse_student_from_json(const char* json_str, Student* stu);

// Student 结构体 → JSON 对象字符串
void student_to_json(const Student* stu, char* out, size_t out_size);

#endif