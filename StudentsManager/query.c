#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "list.h"
void PageLoop(Node* pHead, int targetShort, int type, const char *searchName, int pageSize, int total, const char *title)
{
    int currentPage = 1;
    char op;
    do
    {
        system("cls"); 
        printf("=============================\n");
        printf("%s\n", title);
        printf("总计匹配人数：%d ，每页展示%d条\n", total, pageSize);
        printf("操作指令：n下一页 / p上一页 / q退出浏览\n");
        printf("=============================\n\n");
        // ==============================================

        Node* cur = pHead->next;
        int skip = (currentPage - 1) * pageSize;
        int showCnt = 0;

        // 跳过前面页匹配数据
        while(cur != pHead && skip > 0)
        {
            int match = 0;
            if(type == 1)
            {
                if(strcmp(cur->stu.name, searchName) == 0)
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
        // 打印当前页数据
        while(cur != pHead && showCnt < pageSize)
        {
            int match = 0;
            if(type == 1)
            {
                if(strcmp(cur->stu.name, searchName) == 0)
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
                    printf("学号：%s  姓名：%s  性别：%s  生日：%d年%d月%d日  地址：%s  手机号：%s  邮箱：%s  入学年份：%d\n",
                        cur->stu.stuId, cur->stu.name,(cur->stu.gender == 'f' || cur->stu.gender == 'F')?"女":"男",
                        cur->stu.birthDate.year, cur->stu.birthDate.month, cur->stu.birthDate.day,
                        cur->stu.address,cur->stu.phoneNumber,cur->stu.Email,cur->stu.enrollmentYear);
                }
                showCnt++;
            }
            cur = cur->next;
        }

        int totalPage = total / pageSize;
        if(total % pageSize != 0) totalPage++;
        printf("\n当前页 %d / 总页数 %d\n",currentPage,totalPage);
        printf("操作命令(n/p/q)：");
        scanf(" %c",&op);

        switch (op)
        {
            case 'n':
            case 'N':
                if (currentPage < totalPage)
                {
                    currentPage++;
                }
                else printf("已是最后一页，无法下翻\n");
                break;
            case 'p':
            case 'P':
                if (currentPage > 1)
                {
                    currentPage--;
                }
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
        if(op != 'q' && op != 'Q')
        {
            system("pause");
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

int ShowAllSameName(Node* pHead, const char* n)
{
    assert(pHead && n);
    int total = CountSameName(pHead,n);
    if(total == 0)
    {
        printf("无姓名为%s的学生\n",n);
        return 0;
    }
    const int pageSize = 10;
    // 传入标题、名字字符串，不再强转指针存int
    char title[128];
    sprintf(title, "姓名检索：%s", n);
    PageLoop(pHead, 0, 1, n, pageSize, total, title);
    return 1;
}

int ShowAllSameBirthYear(Node* pHead, int birthyear)
{
    assert(pHead && birthyear);
    if(birthyear < 1900 || birthyear > 2099)
    {
        printf("输入年份%d不合法！请输入1900-2099之间的四位完整年份\n",birthyear);
        return 0;
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
        return 0;
    }
    const int pageSize = 10;
    char title[128];
    sprintf(title, "出生年后两位检索：%02d年", targetShort);
    PageLoop(pHead, targetShort, 2, "", pageSize, total, title);
    return 1;
}

int ShowAllSameEnrollmentYear(Node* pHead, int enteryear)
{
    assert(pHead && enteryear);
    if(enteryear < 1900 || enteryear > 2099)
    {
        printf("输入年份%d不合法！请输入1900-2099之间的四位完整年份\n",enteryear);
        return 0;
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
        return 0;
    }
    const int pageSize = 10;
    char title[128];
    sprintf(title, "入学年份检索：%d年", targetShort);
    PageLoop(pHead, targetShort, 3, "", pageSize, total, title);
    return 1;
}

int ShowAllInformation(Node* pHead)
{
    assert(pHead);
    Node* cur = pHead->next;
    int total = 0;
    while(cur != pHead)
    {
        total++;
        cur = cur->next;
    }
    const int pageSize = 10;
    // 全部学生标题
    PageLoop(pHead, 0, 4, "", pageSize, total, "全部学生信息浏览");
    return 1;
}