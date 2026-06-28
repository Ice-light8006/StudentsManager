#include "mainmenu.h"
#include "querymenu.h"

void showMainMenu()
{
	printf("===========================\n");
	printf("欢迎使用学生信息管理系统\n");
	printf("===========================\n");
	printf("%d.查询系统\n", QUERY);
	printf("%d.退出程序\n", EXIT);
	
}

void choseOperate()
{
	int flag = 1;
	while (flag)
	{
		system("cls");
		showMainMenu();
		printf("请你的操作序号:\n");
		int op;
		if (!(scanf("%d", &op) == 1))
		{
			system("cls");
			showMainMenu();
			printf("输入的字符非法，请重新输入\n");
			continue;
		}
		switch (op)
		{
		case QUERY:
			showQueryMenu();
			choseQueryOperate();
			break;
		case EXIT:
			exit(0);//无论传入什么都会退出程序
			break;
		default:
			system("cls");
			showMainMenu();
			printf("输入的操作不存在，请重新输入\n");
			continue;
		}
	}
}