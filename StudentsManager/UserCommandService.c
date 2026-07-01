#include "UserCommandService.h"

int addStudent(Node* pHead)
{
	
	printf("请输入要添加的学生的学号：（最大长度为127）");
	char stuId[128];
	get_line(stuId, sizeof(stuId));

	printf("请输入要添加的学生的姓名：（最大长度为63）");
	char name[64];
	get_line(name,sizeof(name));

	printf("请输入要添加的学生的性别（M为男，F为女）：");
	char gender;
	scanf(" %c", &gender);

	printf("请输入要添加的学生的生日\n");
	printf("格式：年 月 日（例如2005 2 15表示2005年2月15号，并且年、月、日之间要用空格分开）");
	int year, month, day;
	if ((scanf("%d %d %d", &year, &month, &day)) != 3)
	{
		printf("年份输入错误\n");
		system("pause");
		return 0;
	}

	//清空输入缓冲区
	while (getchar() != '\n');

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
	scanf("%d", &enrollmentYear);

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
	Node* tmp = pHead;
	Node* res = NULL;
	res = ListFind(pHead, stuId);
	if (res == NULL)
	{
		printf("没有学号为%s的学生", stuId);
		return 0;
	}
	else
	{
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
	}
	return 1;
}