
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