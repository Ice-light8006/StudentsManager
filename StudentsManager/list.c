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
    node->stu = *stu;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

Node* ListCreate() {
    Student emptyStu = { 0 };
    Node* pHead = BuyListNode(&emptyStu);
    pHead->next = pHead;
    pHead->prev = pHead;
    return pHead;
}

void ListInsert(Node* pos, const Student* stu) {
    assert(pos);
    Node* newnode = BuyListNode(stu);
    Node* prevNode = pos->prev;
    prevNode->next = newnode;
    newnode->prev = prevNode;
    newnode->next = pos;
    pos->prev = newnode;
}

int ListPushBack(Node* pHead, const Student* stu) {
    assert(pHead);
    if (!pHead) {
        printf("  \033[31m错误，头结点为空指针\033[0m\n");
        return 0;
    }
    ListInsert(pHead, stu);
    return 1;
}

void ListErase(Node* pos) {
    assert(pos);
    pos->prev->next = pos->next;
    pos->next->prev = pos->prev;
    free(pos);
}

void ListRemoveByStuId(Node* pHead, const char* stuId) {
    assert(pHead && stuId);
    Node* cur = pHead->next;
    while (cur != pHead) {
        if (strcmp(cur->stu.stuId, stuId) == 0) {
            ListErase(cur);
            printf("  \033[32m学号为 %s 的学生已删除\033[0m\n", stuId);
            return;
        }
        cur = cur->next;
    }
    printf("  \033[31m未找到学号为 %s 的学生\033[0m\n", stuId);
}

Node* ListFind(Node* pHead, const char* stuId) {
    assert(pHead && stuId);
    Node* cur = pHead->next;
    while (cur != pHead) {
        if (strcmp(cur->stu.stuId, stuId) == 0) return cur;
        cur = cur->next;
    }
    return NULL;
}

void ListModifyName(Node* pHead, const char* stuId, const char* newName) {
    assert(pHead && stuId && newName);
    Node* target = ListFind(pHead, stuId);
    if (target) {
        strcpy(target->stu.name, newName);
        printf("  \033[32m学号 %s 的姓名已修改为 %s\033[0m\n", stuId, newName);
    }
    else {
        printf("  \033[31m未找到学号为 %s 的学生，无法修改\033[0m\n", stuId);
    }
}

void ListModifyBirthday(Node* pHead, const char* stuId, int year, int month, int day) {
    assert(pHead && stuId);
    Node* target = ListFind(pHead, stuId);
    if (target) {
        target->stu.birthDate.year = year;
        target->stu.birthDate.month = month;
        target->stu.birthDate.day = day;
        printf("  \033[32m学号 %s 的生日已修改为 %d-%02d-%02d\033[0m\n", stuId, year, month, day);
    }
    else {
        printf("  \033[31m未找到学号为 %s 的学生，无法修改\033[0m\n", stuId);
    }
}

void ListModifyPhone(Node* pHead, const char* stuId, const char* newPhone) {
    assert(pHead && stuId && newPhone);
    Node* target = ListFind(pHead, stuId);
    if (target) {
        if (strlen(newPhone) >= 32) {
            printf("  \033[31m手机号长度超过32位限制，修改失败\033[0m\n");
            return;
        }
        strcpy(target->stu.phoneNumber, newPhone);
        printf("  \033[32m学号 %s 的手机号已修改为 %s\033[0m\n", stuId, newPhone);
    }
    else {
        printf("  \033[31m未找到学号为 %s 的学生，无法修改\033[0m\n", stuId);
    }
}

void ListModifyEmail(Node* pHead, const char* stuId, const char* newEmail) {
    assert(pHead && stuId && newEmail);
    Node* target = ListFind(pHead, stuId);
    if (target) {
        if (strlen(newEmail) >= 64) {
            printf("  \033[31m邮箱长度超过64位限制，修改失败\033[0m\n");
            return;
        }
        strcpy(target->stu.Email, newEmail);
        printf("  \033[32m学号 %s 的邮箱已修改为 %s\033[0m\n", stuId, newEmail);
    }
    else {
        printf("  \033[31m未找到学号为 %s 的学生，无法修改\033[0m\n", stuId);
    }
}

void ListModifyAddress(Node* pHead, const char* stuId, const char* newAddress) {
    assert(pHead && stuId && newAddress);
    Node* target = ListFind(pHead, stuId);
    if (target) {
        if (strlen(newAddress) >= 128) {
            printf("  \033[31m地址长度超过128位限制，修改失败\033[0m\n");
            return;
        }
        strcpy(target->stu.address, newAddress);
        printf("  \033[32m学号 %s 的地址已修改为 %s\033[0m\n", stuId, newAddress);
    }
    else {
        printf("  \033[31m未找到学号为 %s 的学生，无法修改\033[0m\n", stuId);
    }
}

void ListModifyEnrollmentYear(Node* pHead, const char* stuId, int enrollmentYear) {
    assert(pHead && stuId && enrollmentYear);
    Node* target = ListFind(pHead, stuId);
    if (target) {
        target->stu.enrollmentYear = enrollmentYear;
        printf("  \033[32m学号 %s 的入学年份已修改为 %d\033[0m\n", stuId, enrollmentYear);
    }
    else {
        printf("  \033[31m未找到学号为 %s 的学生，无法修改\033[0m\n", stuId);
    }
}

int ListGetLength(Node* pHead) {
    int cnt = 0;
    Node* tmp = pHead;
    while (tmp->next != pHead) {
        cnt++;
        tmp = tmp->next;
    }
    return cnt;
}