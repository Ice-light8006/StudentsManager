#ifndef __STUDENT_H__
#define __STUDENT_H__

//日期结构体
typedef struct date
{
	int year;					//年
	int month;					//月
	int day;					//日
}Date;

//学生结构体
typedef struct student
{
	char stuId[128];			//学号
	char name[64];				//姓名
	char gender;				//F代表female（女生），M代表male（男生）
	Date birthDate;				//生日
	char address[128];			//地址
	char phoneNumber[32];		//手机号
	char Email[64];				//邮箱
}Student;



#endif