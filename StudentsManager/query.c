#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "list.h"
int CountSameName(Node* pHead, const char* n)
{
    assert(pHead && n);
    Node* cur = pHead->next;
    int cnt = 0;
    while(cur != pHead)
    {
        if(strcmp(cur->stu.name,n) == 0)
            cnt++;
        cur = cur->next;
    }
    return cnt;
}
void ShowAllSameName(Node* pHead, const char* n)
{
    assert(pHead && n);
    int total = CountSameName(pHead,n);
    if(total == 0)
    {
        printf("无改名学生\n");
        return;
    }
    printf("一共找到 %d 位同名学生：\n",total);
    Node* cur = pHead->next;
    while(cur != pHead)
    {
        if((strcmp(cur->stu.name,n)) == 0)
        {
            printf("学号：%s  姓名：%s  入学年份：%d\n",cur->stu.stuId,cur->stu.name,cur->stu.enrollmentYear);
        }
        cur = cur->next;
    }
}

void ShowAllSameBirthYear(Node* pHead, int birthyear)
{
    assert(pHead && birthyear);
    if(birthyear < 1900 || birthyear > 2099)
    {
        printf("输入年份%d不合法！请输入1900-2099之间的四位完整年份\n",birthyear);
        return;
    }
    Node* cur = pHead->next;
    int targetShort = birthyear % 100;
    int total = 0;
    while(cur != pHead)
    {
        if((cur->stu.birthDate.year % 100) == targetShort)
        {
            total++;
        }
        cur = cur->next;
    }
    if(total == 0)
    {
        printf("未找到后两位为%02d年出生的学生\n",targetShort);
        return;
    }
    printf("=============================\n");
    printf("一共找到 %d 位%02d年出生的同学\n",total,targetShort);
    printf("每页最多展示10条，n下一页 / p上一页 / q退出浏览\n");
    printf("=============================\n");
    const int pageSize = 10;
    int currentPage = 1;
    char op;
    do
    {
        cur = pHead->next;
        int skip = (currentPage - 1)*pageSize;
        int showCnt = 0;
        while(cur != pHead && skip >0)
        {
            if((cur->stu.birthDate.year % 100) == targetShort)
                skip--;
            cur = cur->next;
        }
        printf("【第%d页】\n",currentPage);
        while(cur != pHead && showCnt < pageSize)
        {
            if((cur->stu.birthDate.year % 100) == targetShort)
            {
                printf("学号：%s  姓名：%s  生日：%d年%d月%d日\n",cur->stu.stuId,cur->stu.name,cur->stu.birthDate.year,cur->stu.birthDate.month,cur->stu.birthDate.day);
                showCnt++;
            }
            cur = cur->next;
        }
        int totalPage = total / pageSize;
        if(total % pageSize != 0) totalPage++;
        printf("当前页 %d / 总页数 %d\n",currentPage,totalPage);
        printf("操作命令(n/p/q)：");
        scanf("%c",&op);
        switch (op)
        {
            case 'n':
            case 'N':
                if(currentPage < totalPage) currentPage++;
                else printf("已是最后一页，无法下翻\n");
                break;
            case 'p':
            case 'P':
                if(currentPage > 1) currentPage--;
                else printf("已是第一页，无法上翻\n");
                break;
            case 'q':
            case 'Q':
                printf("结束学生浏览\n");
                break;
            default:
                printf("输入无效，仅支持n p q\n");
                break;
        }
    }while(op != 'q' && op != 'Q');
}

void ShowAllSameEnrollmentYear(Node* pHead, int enrollmentyear)
{
    assert(pHead && enrollmentyear);
    if(enrollmentyear < 1900 || enrollmentyear > 2099)
    {
        printf("输入年份%d不合法！请输入1900-2099之间的四位完整年份\n",enrollmentyear);
        return;
    }
    Node* cur = pHead->next;
    int targetShort = enrollmentyear;
    int total = 0;
    while(cur != pHead)
    {
        if(cur->stu.enrollmentYear == targetShort)
        {
            total++;
        }
        cur = cur->next;
    }
    if(total == 0)
    {
        printf("未找到入学年份为%d的学生\n",targetShort);
        return;
    }
    printf("=============================\n");
    printf("一共找到 %d 位入学年份为%d的同学\n",total,targetShort);
    printf("每页最多展示10条，n下一页 / p上一页 / q退出浏览\n");
    printf("=============================\n");
    const int pageSize = 10;
    int currentPage = 1;
    char op;
    do
    {
        cur = pHead->next;
        int skip = (currentPage - 1)*pageSize;
        int showCnt = 0;
        while(cur != pHead && skip >0)
        {
            if(cur->stu.enrollmentYear == targetShort)
                skip--;
            cur = cur->next;
        }
        printf("【第%d页】\n",currentPage);
        while(cur != pHead && showCnt < pageSize)
        {
            if(cur->stu.enrollmentYear == targetShort)
            {
                printf("学号：%s  姓名：%s  入学年份：%d\n",cur->stu.stuId,cur->stu.name,cur->stu.enrollmentYear);
                showCnt++;
            }
            cur = cur->next;
        }
        int totalPage = total / pageSize;
        if(total % pageSize != 0) totalPage++;
        printf("当前页 %d / 总页数 %d\n",currentPage,totalPage);
        printf("操作命令(n/p/q)：");
        scanf("%c",&op);
        switch (op)
        {
            case 'n':
            case 'N':
                if(currentPage < totalPage) currentPage++;
                else printf("已是最后一页，无法下翻\n");
                break;
            case 'p':
            case 'P':
                if(currentPage > 1) currentPage--;
                else printf("已是第一页，无法上翻\n");
                break;
            case 'q':
            case 'Q':
                printf("结束学生浏览\n");
                break;
            default:
                printf("输入无效，仅支持n p q\n");
                break;
        }
    }while(op != 'q' && op != 'Q');
}