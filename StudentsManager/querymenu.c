#include "Querymenu.h"
#include "Query.h"
#include "main.h"
#include "Utils.h"

static void turnToQueryMenu()
{
	system("pause");
	system("cls");
	showQueryMenu();
}

void showQueryMenu()
{
	system("cls");
	printf("==========================\n");
	printf("查询菜单\n");
	printf("==========================\n");
	printf("%d.按姓名查询\n", QUERYNAME);
	printf("%d.按出生年份查询\n", QUERYBIRTHYEAR);
	printf("%d.按入学年份查询\n", QUERYENROLLMENT);
	printf("%d.查询所有学生的信息\n", QUERYALL);
	printf("%d.退出查询模式\n", QUERYEXIT);
}

void choseQueryOperate()
{
	int flag = 1;
	while (flag)
	{
		printf("请输入你的操作序号：");
		int op;
		char nametmp[64];
		int yeartmp = -1;
		scanf("%d", &op);
		//清空输入缓冲区
		while (getchar() != '\n');
		switch (op)
		{
		case QUERYNAME:
			printf("请输入姓名：");
			if (!get_line(nametmp, sizeof(nametmp)))//这个函数成功返回0
			{
				// 去掉末尾的换行符
				size_t len = strlen(nametmp);
				if (len > 0 && nametmp[len - 1] == '\n')
					nametmp[len - 1] = '\0';
				system("cls");
				if (!ShowAllSameName(head, nametmp))
				{
					turnToQueryMenu();
					continue;
				}
			}
			turnToQueryMenu();
			break;
		case QUERYBIRTHYEAR:
			printf("请输入生日年份：\n");
			scanf("%d", &yeartmp);
			system("cls");
			if (!ShowAllSameBirthYear(head, yeartmp))
			{
				turnToQueryMenu();
				continue;
			}
			turnToQueryMenu();
			break;
		case QUERYENROLLMENT:
			printf("请输入入学年份：\n");
			scanf("%d", &yeartmp);
			system("cls");
			if (!ShowAllSameEnrollmentYear(head, yeartmp))
			{
				turnToQueryMenu();
				continue;
			}
			turnToQueryMenu();
			break;
		case QUERYALL:
			system("cls");
			if (!ShowAllInformation(head))
			{
				turnToQueryMenu();
				continue;
			}
			turnToQueryMenu();
			break;
		case QUERYEXIT:
			flag = 0;
			system("cls");
			showMainMenu();
			choseOperate();
			break;
		default:
			printf("输入非法，请重新输入s\n");
			continue;
		}
	}
}