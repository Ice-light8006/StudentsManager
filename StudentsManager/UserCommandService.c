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
	printf("请输入要添加的学生的学号：（最大长度为127）");
	char stuId[128];
	get_line(stuId, sizeof(stuId));
	if (isStuIdExist(pHead, stuId))
	{
		printf("错误，学号为%s的学生已经存在了\n", stuId);
		return 0;
	}

	printf("请输入要添加的学生的姓名：（最大长度为63）");
	char name[64];
	get_line(name, sizeof(name));

	printf("请输入要添加的学生的性别（M为男，F为女）：");
	char gender;
	scanf(" %c", &gender);

	if (!isGenderValid(gender))
	{
		printf("错误，输入的性别不合法！\n");
		return 0;
	}

	printf("请输入要添加的学生的生日（仅支持1900到2099年）\n");
	printf("格式：年 月 日（例如2005 2 15表示2005年2月15号，并且年、月、日之间要用空格分开）");
	int year, month, day;
	if ((scanf("%d %d %d", &year, &month, &day)) != 3)
	{
		clearInputBuffer();
		printf("日期输入错误\n");
		system("pause");
		return 0;
	}

	if (!isDateValid(year, month, day))
	{
		clearInputBuffer();
		printf("错误，输入的日期不合法！\n");
		system("pause");
		return 0;
	}

	//清空输入缓冲区
	clearInputBuffer();

	printf("请输入要添加的学生的地址：（最大长度为127）");
	char address[128];
	get_line(address, sizeof(address));

	printf("请输入要添加的学生的电话号码：（最大长度为31）");
	char phoneNumber[32];
	get_line(phoneNumber, sizeof(phoneNumber));

	printf("请输入要添加学生的邮箱地址：（最大长度为63）");
	char Email[64];
	get_line(Email, sizeof(Email));

	printf("请输入要添加的学生的入学年份：");
	int enrollmentYear;

	if (scanf("%d", &enrollmentYear) != 1)
	{
		clearInputBuffer();
		printf("错误，输入的入学年份不合法！\n");
		system("pause");
		return 0;
	}

	if (!isYearValid(enrollmentYear))
	{
		printf("错误，输入的入学年份不合法！\n");
		return 0;
	}

	clearInputBuffer();

	Date birthDay = { year,month,day };
	Student* stu = (Student*)malloc(sizeof(Student));
	if (stu == NULL)
	{
		printf("内存分配失败\n");
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
		printf("您输入的学生的信息如下：\n");
		displayStudent(stu);
		printf("请检查您的输入的数据是否正确\n");
		printf("如果正确，请输入y然后回车以继续\n");
		printf("如果不正确，请输入n然后回车回退到查询菜单\n");
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
			printf("输入非法，请重新输入\n");
		}
	}

}

int deleteStudent(Node* pHead)
{
	char stuId[128];
	printf("请输入你要删除的学生的学号：（不超过127位）");
	get_line(stuId, sizeof(stuId));
	if (!isStuIdExist(pHead, stuId))
	{
		printf("没有学号为%s的学生", stuId);
		return 0;
	}
	Node* res = NULL;
	res = ListFind(pHead, stuId);
	int flag = 1;
	while (flag)
	{
		printf("该学生信息如下：\n");
		displayStudentNode(res);
		printf("你确定要删除吗？");
		printf("如果你确定要删除，请输入y然后回车\n");
		printf("如果你不删除，请输入n然后回车\n");
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
			printf("===========================\n");
			printf("输入的数字无效，请重新输入\n");
			printf("===========================\n");
		}
	}
	return 1;
}



void randomPickStudent(Node* pHead)
{
	int total = ListGetLength(pHead);
	if (total == 0) {
		printf("系统无学生数据，无法抽取！\n");
		return;
	}

	printf("您想随机抽取几个学生？：");
	int pickNum;
	scanf("%d", &pickNum);

	clearInputBuffer();//清空输入缓冲区

	if (pickNum <= 0 || pickNum > total) pickNum = 1; // 防御性编程

	// 创建一个临时链表，专门用来装载随机抽取到的学生
	Node* tempHead = ListCreate();

	// 循环随机抽取，并复制进临时链表
	for (int i = 0; i < pickNum; i++) {
		int randomIndex = rand() % total;
		Node* cur = pHead->next;
		for (int j = 0; j < randomIndex; j++) {
			cur = cur->next;
		}
		// 将抽到的学生节点信息压入临时链表
		ListPushBack(tempHead, &(cur->stu));
	}

	printf("\n========= 随机抽取结果 =========\n");

	// 直接调用 Query 模块现成的展示函数！
	// 此时展示的功能和查询模块完全一致，包含完整的个人信息和自动分页能力！
	ShowAllInformation(tempHead);

	printf("===============================\n");

	// 释放临时链表占用的内存（不释放会造成内存泄漏）
	Node* delNode = tempHead->next;
	while (delNode != tempHead) {
		Node* nextNode = delNode->next;
		free(delNode);      // 释放节点自身
		delNode = nextNode;
	}
	free(tempHead);         // 释放哨兵头结点
}

int Modify(Node* pHead)
{
	printf("请输入要修改的学生的学号：");
	char stuId[128];
	get_line(stuId, sizeof(stuId));
	if (ListFind(pHead, stuId) == NULL)
	{
		printf("未找到该学号的学生\n");
		system("pause");
		return 0;
	}
	Node* cur = pHead->next;
	while (cur != pHead)
	{
		if (strcmp(cur->stu.stuId, stuId) == 0)
		{
			break;
		}
		cur = cur->next;
	}
	displayStudent(cur);
	printf("请输入要修改的信息：\n");

	printf("1. 姓名\n");

	printf("2. 性别\n");

	printf("3. 出生日期\n");

	printf("4. 地址\n");

	printf("5. 电话号码\n");

	printf("6. 邮箱\n");

	printf("7. 入学年份\n");

	printf("0. 退出\n");

	int choice;

	char gender;

	int year;
	int month;
	int day;

	scanf("%d", &choice);

	clearInputBuffer();

	switch (choice)

	{

	case 1:

		printf("请输入新的姓名：");
		get_line(cur->stu.name, sizeof(cur->stu.name));
		break;

	case 2:

		printf("请输入新的性别（F/M）：");
		scanf(" %c", &gender);
		clearInputBuffer();
		if (gender != 'F' && gender != 'M')
		{
			printf("错误，性别输入非法\n");
			return 0;
		}
		cur->stu.gender = gender;
		break;

	case 3:

		printf("请输入新的出生日期（YYYY-MM-DD）：");
		if (scanf("%d-%d-%d", &year, &month, &day) != 3)
		{
			printf("错误，日期输入错误\n");
			clearInputBuffer();
			return 0;
		}
		if (!isDateValid(year,month,day))
		{
			printf("错误，输入的日期非法\n");
			clearInputBuffer();
			return 0;
		}
		cur->stu.birthDate.year = year;
		cur->stu.birthDate.month = month;
		cur->stu.birthDate.day = day;
		break;

	case 4:

		printf("请输入新的地址：");
		get_line(cur->stu.address, sizeof(cur->stu.address));
		break;

	case 5:

		printf("请输入新的电话号码：");
		get_line(cur->stu.phoneNumber, sizeof(cur->stu.phoneNumber));
		break;

	case 6:

		printf("请输入新的邮箱：");
		get_line(cur->stu.Email, sizeof(cur->stu.Email));
		break;

	case 7:

		printf("请输入新的入学年份：");
		scanf("%d", &year);
		clearInputBuffer();
		if (!isYearValid(year))
		{
			printf("错误！年份不合法");
			return 0;
		}
		cur->stu.enrollmentYear = year;
		break;

	case 0:

		printf("退出修改\n");
		break;

	default:

		printf("输入错误，请重新输入\n");
		break;
	}
	return 1;
}