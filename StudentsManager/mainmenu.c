#include "mainmenu.h"
#include "querymenu.h"
#include "UserCommandService.h"
#include "main.h"

void showMainMenu()
{
	printf("===========================\n");
	printf("欢迎使用学生信息管理系统\n");
	printf("===========================\n");
	printf("%d.查询系统\n", QUERY);
	printf("%d.添加学生\n", ADD);
	printf("%d.删除学生\n", DELETE);
	printf("%d.退出程序\n", EXIT);
}

void choseOperate()
{
	int flag = 1;
	while (flag)
	{
		system("cls");
		showMainMenu();
		printf("请你的操作序号:");
		int op;
		if (!(scanf("%d", &op) == 1))
		{
			system("cls");
			showMainMenu();
			printf("输入的字符非法，请重新输入\n");
			continue;
		}
		//清空输入缓冲区
		while (getchar() != '\n');
		switch (op)
		{
		case QUERY:
			showQueryMenu();
			choseQueryOperate();
			break;
		case ADD:
			if (addStudent(head))
			{
				char* stuInfo = students_to_json(head);
				writeStuInfo(stuInfo);
				printf("添加成功\n");
				system("pause");
				continue;
			}
			else
			{
				printf("添加失败\n");
				system("pause");
				continue;
			}
			break;
		case DELETE:
			if (deleteStudent(head))
			{
				printf("删除成功\n");
				char* stuInfo = students_to_json(head);
				writeStuInfo(stuInfo);
				system("pause");
				continue;
			}
			else
			{
				printf("删除失败\n");
				system("pause");
				continue;
			}
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