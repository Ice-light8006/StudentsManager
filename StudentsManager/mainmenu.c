#include "mainmenu.h"
#include "querymenu.h"
#include "UserCommandService.h"
#include "main.h"

void showMainMenu()
{
	printf("\n");
	// 顶部框线 + 居中的标题
	printf("  \033[36m╔═══════════════════════════════════════╗\033[0m\n");
	printf("  \033[36m║\033[1;33m      欢迎使用学生信息管理系统      \033[0;36m║\033[0m\n");
	printf("  \033[36m╚═══════════════════════════════════════╝\033[0m\n");
	printf("\n");

	// 1. 数据操作组
	printf("  \033[1;32m 数据操作\033[0m\n");
	printf("    \033[33m%d\033[0m. 添加学生\n", ADD);
	printf("    \033[33m%d\033[0m. 删除学生\n", DELETE);
	printf("    \033[33m%d\033[0m. 修改学生信息\n", MODIFY);
	printf("\n");

	// 2. 信息查询组
	printf("  \033[1;34m 信息查询\033[0m\n");
	printf("    \033[33m%d\033[0m. 查询系统\n", QUERY);
	printf("    \033[33m%d\033[0m. 随机抽取学生\n", PICK);
	printf("\n");

	// 3. 系统功能组
	printf("  \033[1;31m 系统功能\033[0m\n");
	printf("    \033[31m%d\033[0m. 退出程序\n", EXIT);
	printf("\n");

	// 底部边界线
	printf("  \033[36m===========================================\033[0m\n");
	printf("\033[0m"); // 确保颜色彻底重置，防止污染后续输入
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
			printf("输入的字符非法，请重新输入\n");
			system("pause");
			system("cls");
			showMainMenu();
			clearInputBuffer();			
			continue;
		}
		//清空输入缓冲区
		clearInputBuffer();
		switch (op)
		{
			//查询
		case QUERY:
			showQueryMenu();
			choseQueryOperate();
			break;
			//添加学生
		case ADD:
			if (addStudent(head))
			{
				char* stuInfo = students_to_json(head);
				writeStuInfo(stuInfo);
				free(stuInfo);
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
			//删除学生
		case DELETE:
			if (deleteStudent(head))
			{
				printf("删除成功\n");
				char* stuInfo = students_to_json(head);
				writeStuInfo(stuInfo);
				free(stuInfo);
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
			//随机抽取学生
		case PICK:
			randomPickStudent(head);
			break;
			//退出程序
		case MODIFY:
			if(Modify(head))
			{
				char* stuInfo = students_to_json(head);
				writeStuInfo(stuInfo);
				free(stuInfo);
				printf("修改成功\n");
				system("pause");
			}
			else
			{
				printf("修改失败\n");
				system("pause");
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