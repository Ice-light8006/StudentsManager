#include "Display.h"

void displayStudent(Student* stu)
{
	printf("学号：%s  姓名：%s  性别：%s  生日：%d年%d月%d日  地址：%s  手机号：%s  邮箱：%s  入学年份：%d\n",
		stu->stuId, stu->name, (stu->gender == 'f' || stu->gender == 'F') ? "女" : "男",
		stu->birthDate.year, stu->birthDate.month, stu->birthDate.day,
		stu->address, stu->phoneNumber, stu->Email, stu->enrollmentYear);
}

void displayStudentValue(Student stu)
{
	printf("学号：%s  姓名：%s  性别：%s  生日：%d年%d月%d日  地址：%s  手机号：%s  邮箱：%s  入学年份：%d\n",
		stu.stuId, stu.name, (stu.gender == 'f' || stu.gender == 'F') ? "女" : "男",
		stu.birthDate.year, stu.birthDate.month, stu.birthDate.day,
		stu.address, stu.phoneNumber, stu.Email, stu.enrollmentYear);
}

void displayStudentNode(Node* tmp)
{
	Student stu = tmp->stu;
	displayStudentValue(stu);
}