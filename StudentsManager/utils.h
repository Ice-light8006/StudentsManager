#ifndef __UTILS_H__
#define __UTILS_H__
#include <stdio.h>
#include <string.h>
#include <time.h>

/**
 * 从标准输入读取一行文本（可包含空格），并自动去掉末尾的换行符。
 * 如果输入为空行（直接按回车），返回空字符串。
 * 如果输入长度超过 buf_size - 1，则只读入前 buf_size-1 个字符，
 * 并将剩余字符丢弃（防止影响下一次输入）。
 *
 * @param buf      存储字符串的缓冲区
 * @param buf_size 缓冲区大小（字节数）
 * @return         成功返回 0，遇到文件末尾（EOF）返回 -1
 */
int get_line(char* buf, size_t buf_size);

int isDateValid(int year, int month, int day);

int isYearValid(int year);

int isGenderValid(char Gender);

void clearInputBuffer(void);

#endif