#include"jsonmanager.h"

#include "jsonmanager.h"

// ---------- 内部工具函数（static，仅在本文件使用） ----------
static const char* find_value_start(const char* json, const char* key) {
    char pattern[256];
    sprintf(pattern, "\"%s\"", key);
    const char* p = strstr(json, pattern);
    if (!p) return NULL;
    p = strchr(p, ':');
    if (!p) return NULL;
    p++;
    while (*p == ' ' || *p == '\t' || *p == '\n') p++;
    return p;
}

static void extract_string(const char* json, const char* key, char* out, size_t out_size) {
    out[0] = '\0';
    const char* p = find_value_start(json, key);
    if (!p || *p != '\"') return;//p为NULL或者p指向的位置不是双引号直接结束函数
    p++;
    size_t i = 0;
    while (*p && *p != '\"' && i < out_size - 1) {//out_size-1，不是out_size，为了给'\0'留位置
        if (*p == '\\' && *(p + 1) == '\"') { p++; }
        out[i++] = *p++;
    }
    out[i] = '\0';
}

static int extract_int(const char* json, const char* key, int default_val) {
    const char* p = find_value_start(json, key);
    if (!p) return default_val;
    return atoi(p);
}

static char extract_char(const char* json, const char* key, char default_val) {
    const char* p = find_value_start(json, key);
    if (!p) return default_val;
    if (*p == '\"') p++;
    return *p;
}

// 提取 JSON 数组中的下一个完整对象（内部使用）
// 简单的说，作用就是从一个 JSON 数组字符串（格式为 [{...},{...},...]）中，逐个提取出每个完整的 {...} 对象。
static int extract_next_object(const char* buf, int pos, char* out, size_t out_size) {
    while (buf[pos] && (buf[pos] == ' ' || buf[pos] == '\t' || buf[pos] == '\n' || buf[pos] == '\r' || buf[pos] == ',')) {
        pos++;
    }
    if (buf[pos] != '{') return -1;

    int start = pos;
    int brace_level = 0;    //大括号层级计数器，用于匹配{}对，遇到{加一，遇到}减一
    int in_quotes = 0;      //标志位，标记当前是否在双引号字符串内部

    for (int i = pos; buf[i]; i++) {            //'\0'的整数值为0，这里的意思就是只要i索引对应的字符不是字符串末尾就继续遍历
        if (buf[i] == '\\') {
            i++;
            continue;
        }
        if (buf[i] == '\"') {
            in_quotes = !in_quotes;
            continue;
        }
        if (!in_quotes) {
            if (buf[i] == '{') {
                brace_level++;
            }
            else if (buf[i] == '}') {
                brace_level--;
                if (brace_level == 0) {
                    int len = i - start + 1;
                    if (len < (int)out_size) {
                        strncpy(out, buf + start, len);
                        out[len] = '\0';
                        return i + 1;
                    }
                    else {
                        return -1;
                    }
                }
            }
        }
    }
    return -1;
}

// ---------- 公开函数实现 ----------
void parse_student_from_json(const char* json_str, Student* stu) {
    memset(stu, 0, sizeof(Student));
    extract_string(json_str, "stuId", stu->stuId, sizeof(stu->stuId));
    extract_string(json_str, "name", stu->name, sizeof(stu->name));
    stu->gender = extract_char(json_str, "gender", 'U');
    stu->birthDate.year = extract_int(json_str, "birthYear", 0);
    stu->birthDate.month = extract_int(json_str, "birthMonth", 0);
    stu->birthDate.day = extract_int(json_str, "birthDay", 0);
    extract_string(json_str, "address", stu->address, sizeof(stu->address));
    extract_string(json_str, "phoneNumber", stu->phoneNumber, sizeof(stu->phoneNumber));
    extract_string(json_str, "Email", stu->Email, sizeof(stu->Email));
    stu->enrollmentYear = extract_int(json_str, "enrollmentYear", 0);
}

void student_to_json(const Student* stu, char* out, size_t out_size) {
    snprintf(out, out_size,
        "{\"stuId\":\"%s\","
        "\"name\":\"%s\","
        "\"gender\":\"%c\","
        "\"birthYear\":%d,"
        "\"birthMonth\":%d,"
        "\"birthDay\":%d,"
        "\"address\":\"%s\","
        "\"phoneNumber\":\"%s\","
        "\"Email\":\"%s\","
        "\"enrollmentYear\":%d}",
        stu->stuId, stu->name, stu->gender,
        stu->birthDate.year, stu->birthDate.month, stu->birthDate.day,
        stu->address, stu->phoneNumber, stu->Email, stu->enrollmentYear);
}

// 从 json 数组中解析所有学生，并插入到链表 pHead 中
int parse_students_from_json_array(const char* json_str, Node* pHead) {
    if (!json_str || !pHead) return 0;
    const char* p = json_str;
    // 找到数组开始的 '['
    while (*p && (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r')) p++;
    if (*p != '[') {
        printf("  \033[31mJSON 数据不是一个数组。\033[0m\n");
        return 0;
    }
    p++;  // 跳过 '['
    int count = 0;
    char obj_buf[2048];
    while (*p) {
        // 跳过空白和逗号
        while (*p && (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r' || *p == ',')) p++;
        if (*p == ']') break;   // 数组结束
        if (*p != '{') {
            printf("  \033[31m警告：预期对象起始 '{'，但找到 '%c'\033[0m\n", *p);
            break;
        }

        // 提取一个完整的对象 {...}
        int brace = 0;
        int in_quotes = 0;
        const char* start = p;
        while (*p) {
            if (*p == '\\') { p++; if (*p) p++; continue; }
            if (*p == '\"') { in_quotes = !in_quotes; p++; continue; }
            if (!in_quotes) {
                if (*p == '{') brace++;
                else if (*p == '}') {
                    brace--;
                    if (brace == 0) {
                        p++; // 跳过 '}'
                        break;
                    }
                }
            }
            p++;
        }
        if (brace != 0) {
            printf("  \033[31m警告：对象括号不匹配\033[0m\n");
            break;
        }

        int len = p - start;
        if (len >= (int)sizeof(obj_buf)) {
            printf("  \033[31m警告：单个对象过长，跳过\033[0m\n");
            continue;
        }
        strncpy(obj_buf, start, len);
        obj_buf[len] = '\0';

        Student stu;
        parse_student_from_json(obj_buf, &stu);
        ListPushBack(pHead, &stu);
        count++;
    }
    return count;
}

char* students_to_json(Node* pHead) {
    if (!pHead) return NULL;

    // 初始缓冲区容量
    size_t capacity = 1024;
    size_t len = 0;
    char* buf = (char*)malloc(capacity);
    if (!buf) return NULL;
    buf[0] = '\0';

    // 写入数组开头
    strcpy(buf, "[\n");
    len = 2;

    Node* cur = pHead->next;
    int first = 1;

    while (cur != pHead) {
        // 将当前学生转为紧凑 JSON（不带换行缩进）
        char stu_json[1024];
        student_to_json(&(cur->stu), stu_json, sizeof(stu_json));

        // 如果不是第一个元素，前面加逗号和换行
        char prefix[10];
        if (first) {
            prefix[0] = '\0';
            first = 0;
        }
        else {
            strcpy(prefix, ",\n");
        }

        // 构造缩进后的对象字符串（每行缩进 2 空格）
        // 格式：  { ... }
        char formatted_obj[1100]; // 留足够空间容纳缩进 + stu_json
        snprintf(formatted_obj, sizeof(formatted_obj), "  %s", stu_json);

        // 计算需要的总长度，并检查是否需要扩容
        size_t needed = len + strlen(prefix) + strlen(formatted_obj) + 2; // +2 for "]\n" or ""
        while (needed >= capacity) {
            capacity *= 2;
            char* tmp = (char*)realloc(buf, capacity);
            if (!tmp) {
                free(buf);
                return NULL;
            }
            buf = tmp;
        }

        // 拼接 prefix 和格式化后的对象
        strcat(buf, prefix);
        strcat(buf, formatted_obj);

        len = strlen(buf);
        cur = cur->next;
    }

    // 添加数组结尾的换行和 ]
    // 先检查容量
    size_t needed = len + 3; // "]\n\0"
    if (needed >= capacity) {
        capacity = needed + 1;
        char* tmp = (char*)realloc(buf, capacity);
        if (!tmp) {
            free(buf);
            return NULL;
        }
        buf = tmp;
    }
    strcat(buf, "\n]");

    return buf;
}