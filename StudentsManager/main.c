#include "list.h"
#include "student.h"
#include "filemanager.h"
#include "query.h"
#include "jsonmanager.h"

int main(int argc, char** argv)
{
	//程序启动时，初始化链表，并读取json文件的数据
	Node* head = ListCreate();
	char* stuInfo = getStuInfo();
	parse_students_from_json_array(stuInfo, head);

	//程序结束时，根据当前链表内的数据生成一个json文本并覆盖写入json文件
	stuInfo = students_to_json(head);
	writeStuInfo(stuInfo);
	return 0;
}