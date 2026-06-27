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

// 从 json 数组中解析所有学生，并插入到链表 pHead 中
int parse_students_from_json_array(const char* json_str, Node* pHead);

// 从程序内部的链表提取数据转换为字符串
char* students_to_json(Node* pHead);

#endif