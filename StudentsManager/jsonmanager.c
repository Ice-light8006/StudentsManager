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
    if (!p || *p != '\"') return;
    p++;
    size_t i = 0;
    while (*p && *p != '\"' && i < out_size - 1) {
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
static int extract_next_object(const char* buf, int pos, char* out, size_t out_size) {
    while (buf[pos] && (buf[pos] == ' ' || buf[pos] == '\t' || buf[pos] == '\n' || buf[pos] == '\r' || buf[pos] == ',')) {
        pos++;
    }
    if (buf[pos] != '{') return -1;

    int start = pos;
    int brace_level = 0;
    int in_quotes = 0;

    for (int i = pos; buf[i]; i++) {
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