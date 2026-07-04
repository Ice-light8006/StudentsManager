#include "utils.h"

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
int get_line(char* buf, size_t buf_size)
{
    if (buf == NULL || buf_size == 0) return -1;

    // 1. 尝试读取一行
    if (fgets(buf, (int)buf_size, stdin) == NULL) {
        // 读取失败（例如 EOF）
        buf[0] = '\0';
        return -1;
    }

    // 2. 查找末尾的换行符，若存在则替换为 '\0' 并返回
    size_t len = strlen(buf);
    if (len > 0 && buf[len - 1] == '\n') {
        buf[len - 1] = '\0';
        return 0;
    }

    // 3. 若没有换行符，说明缓冲区不够长，输入被截断。
    //    此时需要清空 stdin 中剩余的字符，防止干扰下一次输入。
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        // 丢弃多余字符
    }
    return 0;
}

int isDateValid(int year, int month, int day)
{
    // 1. 基础年月范围校验
    if (year < 1900 || year > 2099) return 0;
    if (month < 1 || month > 12) return 0;
    if (day < 1) return 0;

    // 2. 获取当前系统时间
    time_t t = time(NULL);
    struct tm* now = localtime(&t);
    int curYear = now->tm_year + 1900;  // tm_year是从1900年开始算的
    int curMonth = now->tm_mon + 1;     // tm_mon 范围是 0-11，需要 +1
    int curDay = now->tm_mday;

    // 3. 判断输入的日期是否在未来（大于今天）
    if (year > curYear) {
        return 0; // 年份超过今年，非法
    }
    else if (year == curYear) {
        if (month > curMonth) {
            return 0; // 年份相等，月份大于本月，非法
        }
        else if (month == curMonth) {
            if (day > curDay) {
                return 0; // 年月相等，日期大于今天，非法
            }
        }
    }

    // 4. 确定该月对应的最大天数（闰年判断）
    int daysInMonth[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        daysInMonth[2] = 29;
    }

    // 5. 最终天数范围校验
    if (day > daysInMonth[month]) {
        return 0;
    }

    return 1;
}

int isYearValid(int year)
{
    // 1. 获取当前系统年份
    time_t t = time(NULL);
    struct tm* now = localtime(&t);
    int curYear = now->tm_year + 1900; // tm_year 是从1900年开始算的

    // 2. 校验年份
    if (year > curYear) {
        return 0; // 年份在未来，非法
    }

    return 1; // 年份合法
}

int isGenderValid(char Gender)
{
    if (Gender != 'M' && Gender != 'F')
    {
        return 0;
    }
    return 1;
}

/**
 * 安全地清空标准输入缓冲区中的残余字符（包括回车符）。
 * 如果用户触发了 EOF (Ctrl+Z / Ctrl+D)，也能优雅退出，防止死循环。
 */
void clearInputBuffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        // 读取到的字符直接丢弃，不做任何处理
    }
}