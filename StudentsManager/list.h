#ifndef __LIST_H__
#define __LIST_H__
#include "student.h"

typedef struct ListNode
{
	Student stu;					//学生结构体
	struct ListNode* next;			//指向下一个节点
	struct ListNode* prev;			//指向前一个节点
}Node;

// 申请一个新节点
Node* BuyListNode(const Student* stu);

// 创建并初始化带头双向链表（返回哨位头结点）
Node* ListCreate();

// 在 pos 位置之前插入新节点（核心插入逻辑）
void ListInsert(Node* pos, const Student* stu);

// 尾插法（在链表尾部插入新学生）
void ListPushBack(Node* pHead, const Student* stu);

// 删除 pos 位置的节点，不能删除哨位头结点
void ListErase(Node* pos);

// 按学号删除学生（综合应用）
void ListRemoveByStuId(Node* pHead, const char* stuId);

// 按学号查找学生，找到返回节点指针，找不到返回 NULL
Node* ListFind(Node* pHead, const char* stuId);

// 按学号修改学生姓名
void ListModifyName(Node* pHead, const char* stuId, const char* newName);

// 按学号修改学生生日
void ListModifyBirthday(Node* pHead, const char* stuId, int year, int month, int day);

// 按学号修改学生手机号
void ListModifyPhone(Node* pHead, const char* stuId, const char* newPhone);

// 按学号修改学生邮箱
void ListModifyEmail(Node* pHead, const char* stuId, const char* newEmail);

// 按学号修改学生地址
void ListModifyAddress(Node* pHead, const char* stuId, const char* newAddress);

// 按学号修改学生地址
void ListModifyAddress(Node* pHead, const char* stuId, const char* newAddress);

// 按学号修改学生入学年份
void ListModifyEnrollmentYear(Node* pHead, const char* stuId, int enrollmentYear);

//获取链表总长度
int ListGetLength(Node* pHead);

#endif