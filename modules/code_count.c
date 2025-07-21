#include <io.h>
#include <direct.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student_management.h"

#define MAX 256  // 定义最大路径长度

long total;  // 用于存储总行数

// 函数声明
int countLines(const char *filename);  // 统计单个文件的行数
void findAllCFiles(const char *path, long *total);  // 查找所有C文件
void findAllSubDirs(const char *path, long *total);  // 查找所有子目录
void safePathConcat(char *dest, size_t destSize, const char *dir, const char *file);  // 安全拼接路径

// 新增的代码统计功能函数
void run_code_count() {
    char path[MAX] = ".";  // 默认当前目录
    long total = 0;  // 初始化总行数为0

    printf("统计中...\n");  // 提示用户正在统计

    findAllCFiles(path, &total);  // 统计当前目录下的C文件
    findAllSubDirs(path, &total);  // 统计子目录中的C文件

    printf("当前共写了 %ld 行代码。\n", total);  // 输出统计结果
}

// 主函数（保留原有功能，但将其重命名为test_code_count以便测试）
int test_code_count() {
    char path[MAX] = ".";  // 默认当前目录
    long total = 0;  // 初始化总行数为0

    printf("统计中...\n");  // 提示用户正在统计

    findAllCFiles(path, &total);  // 统计当前目录下的C文件
    findAllSubDirs(path, &total);  // 统计子目录中的C文件

    printf("当前共写了 %ld 行代码。\n", total);  // 输出统计结果

    return 0;
}

// 统计单个文件的行数
int countLines(const char *filename) {
    FILE *fp;
    int count = 0;
    int temp;
    int prev = '\n';  // 用于记录前一个字符

    // 打开文件
    if ((fp = fopen(filename, "r")) == NULL) {
        fprintf(stderr, "文件打开失败：%s\n", filename);
        return 0;
    }

    // 逐个字符读取文件
    while ((temp = fgetc(fp)) != EOF) {
        if (temp == '\n') {
            count++;  // 遇到换行符则行数+1
        }
        prev = temp;  // 记录当前字符
    }

    // 根据文件结尾情况调整行数
    if (prev != '\n' && count > 0) {
        count++;  // 文件最后没有换行符，但有内容，行数+1
    } else if (count == 0 && prev != EOF) {
        count = 1;  // 空文件但有内容（可能是一个字符），行数+1
    }

    fclose(fp);  // 关闭文件
    return count;  // 返回行数
}

// 查找所有C文件并统计行数
void findAllCFiles(const char *path, long *total) {
    struct _finddata_t fa;  // 文件信息结构体
    long handle;  // 文件句柄
    char thePath[MAX], target[MAX];  // 路径缓冲区

    // 构造搜索路径
    snprintf(thePath, sizeof(thePath), "%s/*.c", path);

    // 开始搜索
    if ((handle = _findfirst(thePath, &fa)) != -1L) {
        do {
            // 跳过. .. ...
            if (strcmp(fa.name, ".") && strcmp(fa.name, "..")) {
                // 构造完整文件路径
                safePathConcat(target, sizeof(target), path, fa.name);
                // 统计文件行数
                int lines = countLines(target);
                // 加到总行数
                *total += lines;
                // 打印文件行数信息
                printf("%s - %d 行\n", target, lines);
            }
        } while (_findnext(handle, &fa) == 0);  // 继续搜索下一个文件
    }

    _findclose(handle);  // 关闭搜索句柄
}

// 查找所有子目录
void findAllSubDirs(const char *path, long *total) {
    struct _finddata_t fa;  // 文件信息结构体
    long handle;  // 文件句柄
    char thePath[MAX], target[MAX];  // 路径缓冲区

    // 构造搜索路径
    snprintf(thePath, sizeof(thePath), "%s/*", path);

    // 开始搜索
    if ((handle = _findfirst(thePath, &fa)) != -1L) {
        do {
            // 跳过. .. ...
            if (strcmp(fa.name, ".") && strcmp(fa.name, "..")) {
                // 如果是子目录
                if (fa.attrib & _A_SUBDIR) {
                    // 构造完整子目录路径
                    safePathConcat(target, sizeof(target), path, fa.name);
                    // 统计子目录中的C文件
                    findAllCFiles(target, total);
                    // 递归查找子目录中的子目录
                    findAllSubDirs(target, total);
                }
            }
        } while (_findnext(handle, &fa) == 0);  // 继续搜索下一个文件
    }

    _findclose(handle);  // 关闭搜索句柄
}

// 安全拼接路径
void safePathConcat(char *dest, size_t destSize, const char *dir, const char *file) {
    // 使用snprintf保证不会溢出
    int len = snprintf(dest, destSize, "%s/%s", dir, file);
    // 如果发生溢出，报错并退出
    if (len >= destSize) {
        fprintf(stderr, "路径拼接溢出：%s/%s\n", dir, file);
        exit(EXIT_FAILURE);
    }
}