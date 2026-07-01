#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "list.h"

// 申请一个新节点
Node* BuyListNode(const Student* stu) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL) {
        perror("malloc failed");
        exit(-1);
    }
    // 将传入的学生信息拷贝到新节点中
    node->stu = *stu;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

// 创建并初始化带头双向链表（返回哨位头结点）
Node* ListCreate() {
    // 创建一个哨位头结点，数据域可以随意初始化（这里清零）
    Student emptyStu = { 0 };
    Node* pHead = BuyListNode(&emptyStu);

    // 初始状态下，前后指针都指向自己，形成闭环
    pHead->next = pHead;
    pHead->prev = pHead;

    return pHead;
}

// 在 pos 位置之前插入新节点（核心插入逻辑）
void ListInsert(Node* pos, const Student* stu) {
    assert(pos); // 确保插入位置合法
    Node* newnode = BuyListNode(stu);
    Node* prevNode = pos->prev;

    // 1. 新节点与前驱节点连接
    prevNode->next = newnode;
    newnode->prev = prevNode;

    // 2. 新节点与后继节点（pos）连接
    newnode->next = pos;
    pos->prev = newnode;
}

// 尾插法（在链表尾部插入新学生）
int ListPushBack(Node* pHead, const Student* stu) {
    assert(pHead);
    // 在哨位头结点之前插入，即为尾插
    if (!pHead)
    {
        printf("错误，头结点为空指针");
        return 0;
    }
    ListInsert(pHead, stu);
    return 1;
}

// 删除 pos 位置的节点，不能删除哨位头结点
void ListErase(Node* pos) {
    assert(pos);
    // 让前驱节点的 next 指向后继节点
    pos->prev->next = pos->next;
    // 让后继节点的 prev 指向前驱节点
    pos->next->prev = pos->prev;

    free(pos); // 释放内存
}

// 按学号删除学生（综合应用）
void ListRemoveByStuId(Node* pHead, const char* stuId) {
    assert(pHead && stuId);
    Node* cur = pHead->next;
    while (cur != pHead) {
        if (strcmp(cur->stu.stuId, stuId) == 0) {
            ListErase(cur);
            printf("学号为 %s 的学生已删除\n", stuId);
            return;
        }
        cur = cur->next;
    }
    printf("未找到学号为 %s 的学生\n", stuId);
}

// 按学号查找学生，找到返回节点指针，找不到返回 NULL
Node* ListFind(Node* pHead, const char* stuId) {
    assert(pHead && stuId);
    Node* cur = pHead->next;
    while (cur != pHead) {
        if (strcmp(cur->stu.stuId, stuId) == 0) {
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}

// 按学号修改学生姓名
void ListModifyName(Node* pHead, const char* stuId, const char* newName) {
    assert(pHead && stuId && newName);
    Node* target = ListFind(pHead, stuId);
    if (target) {
        strcpy(target->stu.name, newName);
        printf("学号 %s 的姓名已修改为 %s\n", stuId, newName);
    }
    else {
        printf("未找到学号为 %s 的学生，无法修改\n", stuId);
    }
}

// 按学号修改学生生日
void ListModifyBirthday(Node* pHead, const char* stuId, int year, int month, int day) {
    assert(pHead && stuId);
    Node* target = ListFind(pHead, stuId);
    if (target) {
        // 直接修改嵌套结构体的成员
        target->stu.birthDate.year = year;
        target->stu.birthDate.month = month;
        target->stu.birthDate.day = day;
        printf("学号 %s 的生日已修改为 %d-%02d-%02d\n",
            stuId, year, month, day);
    }
    else {
        printf("未找到学号为 %s 的学生，无法修改\n", stuId);
    }
}

// 按学号修改学生手机号
void ListModifyPhone(Node* pHead, const char* stuId, const char* newPhone) {
    assert(pHead && stuId && newPhone);
    Node* target = ListFind(pHead, stuId);
    if (target) {
        // 严格检查长度防止溢出（phoneNumber[32]）
        if (strlen(newPhone) >= 32) {
            printf("手机号长度超过32位限制，修改失败\n");
            return;
        }
        strcpy(target->stu.phoneNumber, newPhone);
        printf("学号 %s 的手机号已修改为 %s\n", stuId, newPhone);
    }
    else {
        printf("未找到学号为 %s 的学生，无法修改\n", stuId);
    }
}

// 按学号修改学生邮箱
void ListModifyEmail(Node* pHead, const char* stuId, const char* newEmail) {
    assert(pHead && stuId && newEmail);
    Node* target = ListFind(pHead, stuId);
    if (target) {
        // 严格检查长度（Email[64]）
        if (strlen(newEmail) >= 64) {
            printf("邮箱长度超过64位限制，修改失败\n");
            return;
        }
        strcpy(target->stu.Email, newEmail);
        printf("学号 %s 的邮箱已修改为 %s\n", stuId, newEmail);
    }
    else {
        printf("未找到学号为 %s 的学生，无法修改\n", stuId);
    }
}

// 按学号修改学生地址
void ListModifyAddress(Node* pHead, const char* stuId, const char* newAddress) {
    assert(pHead && stuId && newAddress);
    Node* target = ListFind(pHead, stuId);
    if (target) {
        // 严格检查长度（address[128]）
        if (strlen(newAddress) >= 128) {
            printf("地址长度超过128位限制，修改失败\n");
            return;
        }
        strcpy(target->stu.address, newAddress);
        printf("学号 %s 的地址已修改为 %s\n", stuId, newAddress);
    }
    else {
        printf("未找到学号为 %s 的学生，无法修改\n", stuId);
    }
}

// 按学号修改学生入学年份
void ListModifyEnrollmentYear(Node* pHead, const char* stuId, int enrollmentYear) {
    assert(pHead && stuId && enrollmentYear);
    Node* target = ListFind(pHead, stuId);
    if (target) {
        target->stu.enrollmentYear = enrollmentYear;
        printf("学号 %s 的地址已修改为 %d\n", stuId, enrollmentYear);
    }
    else {
        printf("未找到学号为 %s 的学生，无法修改\n", stuId);
    }
}

// 获取链表总长度
int ListGetLength(Node* pHead)
{
    int cnt = 0;
    Node* tmp = pHead;
    while (tmp->next != pHead)
    {
        cnt++;
        tmp = tmp->next;
    }
    return cnt;
}