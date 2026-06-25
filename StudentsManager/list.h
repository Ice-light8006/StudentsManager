#ifndef __LIST_H__
#define __LIST_H__
#include "student.h"

typedef struct ListNode
{
	Student stu;					//学生结构体
	struct ListNode* next;			//指向下一个节点
	struct ListNode* prev;			//指向前一个节点
}Node;

#endif