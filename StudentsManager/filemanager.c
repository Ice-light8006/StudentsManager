#include "filemanager.h"
#include <stdio.h>
#include <stdlib.h>

//如果出现错误则返回NULL
char* getStuInfo()
{
	FILE* stuInfoFile = fopen(STUINFOFILE, "r");
	int len = 0;
	int capacity = 64;
	char* result = (char*)malloc(capacity);
	if (result == NULL) {
		return NULL;
	}
	int ch;
	while ((ch = fgetc(stuInfoFile)) != EOF)
	{
		if (len + 1 >= capacity)
		{
			capacity = capacity * 2;
			char* tmp = (char*)realloc(result, capacity);
			if (tmp == NULL) {
				free(result);
				return NULL;
			}
			result = tmp;
		}
		result[len] = (char)ch;
		len++;
	}
	if (ferror(stuInfoFile)) {
		free(result);
		return NULL;
	}
	result[len] = '\0';
	fclose(stuInfoFile);
	return result;
}

//失败返回-1，成功返回0
int writeStuInfo(char* text)
{
	FILE* stuInfoFile = fopen(STUINFOFILE, "w");
	if (stuInfoFile == NULL)
	{
		perror("文件打开失败");
		fclose(stuInfoFile);
		return -1;
	}
	if (fputs(text, stuInfoFile) == EOF) {
		perror("写入字符串失败");
		fclose(stuInfoFile);
		return -1;
	}
	fclose(stuInfoFile);
	return 0;
}