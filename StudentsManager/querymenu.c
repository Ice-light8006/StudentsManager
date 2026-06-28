#include "querymenu.h"
#include "query.h"
#include "main.h"

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
	printf("请输入你的操作序号：");
	int flag = 1;
	while (flag)
	{
		int op;
		char nametmp[32];
		int yeartmp = -1;
		scanf("%d", &op);
		switch (op)
		{
		case QUERYNAME:
			// 清掉可能残留在缓冲区的换行符
			while (getchar() != '\n');
			printf("请输入姓名：");
			if (fgets(nametmp, sizeof(nametmp), stdin))
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
			system("pause");
			break;
		case QUERYBIRTHYEAR:
			printf("请输入生日年份：\n");
			scanf("%d", yeartmp);
			system("cls");
			if (!ShowAllSameBirthYear(head, yeartmp))
			{
				turnToQueryMenu();
				continue;
			}
			system("pause");
			break;
		case QUERYENROLLMENT:
			printf("请输入入学年份：\n");
			scanf("%d", yeartmp);
			system("cls");
			if (!ShowAllSameEnrollmentYear(head, yeartmp))
			{
				turnToQueryMenu();
				continue;
			}
			break;
		case QUERYALL:
			system("cls");
			if (!ShowAllInformation(head))
			{
				turnToQueryMenu();
				continue;
			}
			system("pause");
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