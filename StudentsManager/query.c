#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "list.h"
void PageLoop(Node* pHead, int targetShort, int type, int pageSize, int total)
{
    int currentPage = 1;
    char op;
    do
    {
        Node* cur = pHead->next;
        int skip = (currentPage - 1) * pageSize;
        int showCnt = 0;
        // 跳过前面页数据
        while(cur != pHead && skip > 0)
        {
            int match = 0;
            if(type == 1)
            {
                const char* name = (const char*)(size_t)targetShort;
                if(strcmp(cur->stu.name, name) == 0)
                    match = 1;
            }
            else if(type == 2)
            {
                if((cur->stu.birthDate.year % 100) == targetShort)
                    match = 1;
            }
            else if(type == 3)
            {
                if(cur->stu.enrollmentYear == targetShort)
                    match = 1;
            }
            else if(type == 4)
            {
                match = 1;
            }
            if(match)
                skip--;
            cur = cur->next;
        }
        printf("【第%d页】\n",currentPage);
        // 打印当前页
        while(cur != pHead && showCnt < pageSize)
        {
            int match = 0;
            if(type == 1)
            {
                const char* name = (const char*)(size_t)targetShort;
                if(strcmp(cur->stu.name, name) == 0)
                    match = 1;
            }
            else if(type == 2)
            {
                if((cur->stu.birthDate.year % 100) == targetShort)
                    match = 1;
            }
            else if(type == 3)
            {
                if(cur->stu.enrollmentYear == targetShort)
                    match = 1;
            }
            else if(type == 4)
            {
                match = 1;
            }
            if(match)
            {
                if(type == 1)
                {
                    printf("学号：%s  姓名：%s  入学年份：%d\n",cur->stu.stuId,cur->stu.name,cur->stu.enrollmentYear);
                }
                else if(type == 2)
                {
                    printf("学号：%s  姓名：%s  生日：%d年%d月%d日\n",cur->stu.stuId,cur->stu.name,cur->stu.birthDate.year,cur->stu.birthDate.month,cur->stu.birthDate.day);
                }
                else if(type == 3)
                {
                    printf("学号：%s  姓名：%s  入学年份：%d\n",cur->stu.stuId,cur->stu.name,cur->stu.enrollmentYear);
                }
                else if(type == 4)
                {
                    // ShowAllInformation 完整信息打印
                    printf("学号：%s  姓名：%s  性别：%s  生日：%d年%d月%d日  地址：%s  手机号：%s  邮箱：%s  入学年份：%d\n",
                        cur->stu.stuId, cur->stu.name,(cur->stu.gender == 'f' || cur->stu.gender == 'F')?"女":"男",cur->stu.birthDate.year, cur->stu.birthDate.month, cur->stu.birthDate.day,cur->stu.address,cur->stu.phoneNumber,cur->stu.Email,cur->stu.enrollmentYear);
                }
                showCnt++;
            }
            cur = cur->next;
        }
        int totalPage = total / pageSize;
        if(total % pageSize != 0) totalPage++;
        printf("当前页 %d / 总页数 %d\n",currentPage,totalPage);
        printf("操作命令(n/p/q)：");
        scanf(" %c",&op);
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
    const int pageSize = 10;
    PageLoop(pHead, (int)(size_t)n, 1, pageSize, total);
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
    // type=2 出生年后两位
    PageLoop(pHead, targetShort, 2, pageSize, total);
}

void ShowAllSameEnrollmentYear(Node* pHead, int enteryear)
{
    assert(pHead && enteryear);
    if(enteryear < 1900 || enteryear > 2099)
    {
        printf("输入年份%d不合法！请输入1900-2099之间的四位完整年份\n",enteryear);
        return;
    }
    Node* cur = pHead->next;
    int targetShort = enteryear;
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
    // type=3 入学年份
    PageLoop(pHead, targetShort, 3, pageSize, total);
}

void ShowAllInformation(Node* pHead)
{
    assert(pHead);
    Node* cur = pHead->next;
    int total = 0;
    while(cur != pHead)
    {
        total++;
        cur = cur->next;
    }
    printf("=============================\n");
    printf("全部学生信息，总人数：%d\n",total);
    printf("每页最多展示10条，n下一页 / p上一页 / q退出浏览\n");
    printf("=============================\n");
    const int pageSize = 10;
    PageLoop(pHead,0,4,pageSize,total);
}