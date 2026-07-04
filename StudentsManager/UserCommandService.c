#include "UserCommandService.h"

static int isStuIdExist(Node* pHead, const char* stuId)
{
	Node* cur = pHead->next; // 从第一个真实节点开始
	while (cur != pHead)     // 循环直到回到哨兵位
	{
		if (strcmp(cur->stu.stuId, stuId) == 0) return 1;
		cur = cur->next;
	}
	return 0;
}

int addStudent(Node* pHead)
{
	printf("\n  \033[33m请输入要添加的学生的学号：\033[0m（最大长度为127）\n");
	char stuId[128];
	get_line(stuId, sizeof(stuId));
	if (isStuIdExist(pHead, stuId))
	{
		printf("  \033[31m错误，学号为 %s 的学生已经存在了！\033[0m\n", stuId);
		return 0;
	}

	printf("  \033[33m请输入要添加的学生的姓名：\033[0m（最大长度为63）\n");
	char name[64];
	get_line(name, sizeof(name));

	printf("  \033[33m请输入要添加的学生的性别：\033[0m（M为男，F为女）\n");
	char gender;
	scanf(" %c", &gender);

	if (!isGenderValid(gender))
	{
		printf("  \033[31m错误，输入的性别不合法！\033[0m\n");
		return 0;
	}

	printf("  \033[33m请输入要添加的学生的生日：\033[0m（仅支持1900到2099年）\n");
	printf("  格式：年 月 日（例如 2005 2 15 表示2005年2月15号）\n");
	int year, month, day;
	if ((scanf("%d %d %d", &year, &month, &day)) != 3)
	{
		clearInputBuffer();
		printf("  \033[31m日期输入错误\033[0m\n");
		system("pause");
		return 0;
	}

	if (!isDateValid(year, month, day))
	{
		clearInputBuffer();
		printf("  \033[31m错误，输入的日期不合法！\033[0m\n");
		system("pause");
		return 0;
	}

	//清空输入缓冲区
	clearInputBuffer();

	printf("  \033[33m请输入要添加的学生的地址：\033[0m（最大长度为127）\n");
	char address[128];
	get_line(address, sizeof(address));

	printf("  \033[33m请输入要添加的学生的电话号码：\033[0m（最大长度为31）\n");
	char phoneNumber[32];
	get_line(phoneNumber, sizeof(phoneNumber));

	printf("  \033[33m请输入要添加学生的邮箱地址：\033[0m（最大长度为63）\n");
	char Email[64];
	get_line(Email, sizeof(Email));

	printf("  \033[33m请输入要添加的学生的入学年份：\033[0m\n");
	int enrollmentYear;

	if (scanf("%d", &enrollmentYear) != 1)
	{
		clearInputBuffer();
		printf("  \033[31m错误，输入的入学年份不合法！\033[0m\n");
		system("pause");
		return 0;
	}

	if (!isYearValid(enrollmentYear))
	{
		printf("  \033[31m错误，输入的入学年份不合法！\033[0m\n");
		return 0;
	}

	clearInputBuffer();

	Date birthDay;
	birthDay.year = year;
	birthDay.month = month;
	birthDay.day = day;
	Student* stu = (Student*)malloc(sizeof(Student));
	if (stu == NULL)
	{
		printf("  \033[31m内存分配失败\033[0m\n");
		return 0;
	}
	strcpy(stu->stuId, stuId);
	strcpy(stu->name, name);
	stu->gender = gender;
	stu->birthDate = birthDay;
	strcpy(stu->address, address);
	strcpy(stu->phoneNumber, phoneNumber);
	strcpy(stu->Email, Email);
	stu->enrollmentYear = enrollmentYear;

	//让用户确认用户无误
	int flag = 1;
	while (flag)
	{
		system("pause");
		system("cls");
		printf("  \033[36m━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\033[0m\n");
		printf("  \033[1;33m您输入的学生的信息如下：\033[0m\n");
		displayStudent(stu);
		printf("  \033[33m请仔细检查您的输入是否正确：\033[0m\n");
		printf("  \033[32m如果正确，请输入 y 然后回车以继续\033[0m\n");
		printf("  \033[31m如果不正确，请输入 n 然后回车回退到查询菜单\033[0m\n");
		printf("  \033[36m━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\033[0m\n");
		char input;
		scanf(" %c", &input);
		if (input == 'y')
		{
			flag = 0;
			//把结构体尾插到链表
			if (!ListPushBack(pHead, stu))
			{
				free(stu);
				return 0;
			}
			else
			{
				free(stu);
				return 1;
			}
		}
		else if (input == 'n')
		{
			flag = 0;
			free(stu);
			return 0;
		}
		else
		{
			printf("  \033[31m输入非法，请重新输入！\033[0m\n");
		}
	}
}

int deleteStudent(Node* pHead)
{
	printf("\n  \033[33m请输入你要删除的学生的学号：\033[0m（不超过127位）\n");
	char stuId[128];
	get_line(stuId, sizeof(stuId));
	if (!isStuIdExist(pHead, stuId))
	{
		printf("  \033[31m没有学号为 %s 的学生！\033[0m\n", stuId);
		return 0;
	}
	Node* res = NULL;
	res = ListFind(pHead, stuId);
	int flag = 1;
	while (flag)
	{
		printf("  \033[36m━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\033[0m\n");
		printf("  \033[1;33m该学生信息如下：\033[0m\n");
		displayStudentNode(res);
		printf("  \033[33m你确定要删除该学生吗？\033[0m\n");
		printf("  \033[32m如果确定，请输入 y 然后回车\033[0m\n");
		printf("  \033[31m如果不删除，请输入 n 然后回车\033[0m\n");
		printf("  \033[36m━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\033[0m\n");
		char input;
		scanf(" %c", &input);
		if (input == 'y')
		{
			ListErase(res);
			return 1;
		}
		else if (input == 'n')
		{
			return 0;
		}
		else
		{
			system("cls");
			printf("  \033[31m输入的数字无效，请重新输入！\033[0m\n");
		}
	}
	return 1;
}

void randomPickStudent(Node* pHead)
{
	int total = ListGetLength(pHead);
	if (total == 0) {
		printf("  \033[31m系统无学生数据，无法抽取！\033[0m\n");
		return;
	}

	printf("\n  \033[33m您想随机抽取几个学生？：\033[0m ");
	int pickNum;
	scanf("%d", &pickNum);

	clearInputBuffer();//清空输入缓冲区

	if (pickNum <= 0 || pickNum > total) pickNum = 1; // 防御性编程

	// 创建一个临时链表
	Node* tempHead = ListCreate();

	// 循环随机抽取
	for (int i = 0; i < pickNum; i++) {
		int randomIndex = rand() % total;
		Node* cur = pHead->next;
		for (int j = 0; j < randomIndex; j++) {
			cur = cur->next;
		}
		ListPushBack(tempHead, &(cur->stu));
	}

	printf("\n  \033[36m━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\033[0m\n");
	printf("  \033[1;33m          随机抽取结果\033[0m\n");
	printf("  \033[36m━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\033[0m\n");

	ShowAllInformation(tempHead);

	// 释放临时链表
	Node* delNode = tempHead->next;
	while (delNode != tempHead) {
		Node* nextNode = delNode->next;
		free(delNode);
		delNode = nextNode;
	}
	free(tempHead);
}

int Modify(Node* pHead)
{
	printf("\n  \033[33m请输入要修改的学生的学号：\033[0m\n");
	char stuId[128];
	get_line(stuId, sizeof(stuId));
	if (ListFind(pHead, stuId) == NULL)
	{
		printf("  \033[31m未找到该学号的学生！\033[0m\n");
		system("pause");
		return 0;
	}
	Node* cur = pHead->next;
	while (cur != pHead)
	{
		if (strcmp(cur->stu.stuId, stuId) == 0) break;
		cur = cur->next;
	}
	displayStudent(cur);
	printf("\n  \033[36m━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\033[0m\n");
	printf("  \033[1;33m请输入要修改的信息：\033[0m\n");
	printf("  \033[33m1\033[0m. 姓名\n");
	printf("  \033[33m2\033[0m. 性别\n");
	printf("  \033[33m3\033[0m. 出生日期\n");
	printf("  \033[33m4\033[0m. 地址\n");
	printf("  \033[33m5\033[0m. 电话号码\n");
	printf("  \033[33m6\033[0m. 邮箱\n");
	printf("  \033[33m7\033[0m. 入学年份\n");
	printf("  \033[31m0\033[0m. 退出\n");
	printf("  \033[36m━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\033[0m\n");

	int choice;
	char gender;
	int year, month, day;

	scanf("%d", &choice);
	clearInputBuffer();

	switch (choice)
	{
	case 1:
		printf("  \033[33m请输入新的姓名：\033[0m\n");
		get_line(cur->stu.name, sizeof(cur->stu.name));
		break;
	case 2:
		printf("  \033[33m请输入新的性别（F/M）：\033[0m\n");
		scanf(" %c", &gender);
		clearInputBuffer();
		if (gender != 'F' && gender != 'M')
		{
			printf("  \033[31m错误，性别输入非法！\033[0m\n");
			return 0;
		}
		cur->stu.gender = gender;
		break;
	case 3:
		printf("  \033[33m请输入新的出生日期（格式：年 月 日）：\033[0m\n");
		if (scanf("%d %d %d", &year, &month, &day) != 3)
		{
			printf("  \033[31m错误，日期输入错误！\033[0m\n");
			clearInputBuffer();
			return 0;
		}
		if (!isDateValid(year, month, day))
		{
			printf("  \033[31m错误，输入的日期非法！\033[0m\n");
			clearInputBuffer();
			return 0;
		}
		cur->stu.birthDate.year = year;
		cur->stu.birthDate.month = month;
		cur->stu.birthDate.day = day;
		break;
	case 4:
		printf("  \033[33m请输入新的地址：\033[0m\n");
		get_line(cur->stu.address, sizeof(cur->stu.address));
		break;
	case 5:
		printf("  \033[33m请输入新的电话号码：\033[0m\n");
		get_line(cur->stu.phoneNumber, sizeof(cur->stu.phoneNumber));
		break;
	case 6:
		printf("  \033[33m请输入新的邮箱：\033[0m\n");
		get_line(cur->stu.Email, sizeof(cur->stu.Email));
		break;
	case 7:
		printf("  \033[33m请输入新的入学年份：\033[0m\n");
		scanf("%d", &year);
		clearInputBuffer();
		if (!isYearValid(year))
		{
			printf("  \033[31m错误！年份不合法！\033[0m\n");
			return 0;
		}
		cur->stu.enrollmentYear = year;
		break;
	case 0:
		printf("  \033[33m退出修改\033[0m\n");
		break;
	default:
		printf("  \033[31m输入错误，请重新输入！\033[0m\n");
		break;
	}
	return 1;
}