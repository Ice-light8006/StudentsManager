#include "UserCommandService.h"

int addStudent(Node* pHead)
{
	printf("请输入要添加的学生的学号：（最大长度为127）");
	char stuId[128];
	scanf("%127s", stuId);

	printf("请输入要添加的学生的姓名：（最大长度为63）");
	char name[64];
	scanf("%63s", name);

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

	printf("请输入要添加的学生的地址：（最大长度为127）");
	char address[128];
	scanf("%127s", address);

	printf("请输入要添加的学生的电话号码：（最大长度为31）");
	char phoneNumber[32];
	scanf("%31s", phoneNumber);

	printf("请输入要添加学生的邮箱地址：（最大长度为63）");
	char Email[64];
	scanf("%63s", Email);

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
	//把结构体尾插到链表
	if (!ListPushBack(pHead, stu))
	{
		free(stu);
		return 0;
	}
	return 1;
}