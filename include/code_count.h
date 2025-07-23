// code_count.h  改进版
#pragma once

#ifndef CODE_COUNT_H
#define CODE_COUNT_H

// 定义必要类型
#include <stddef.h>  // 为了使用size_t类型

// 公共接口类型定义
typedef struct {
    char filename[256];
    long line_count;
} FileInfo;

typedef struct {
    FileInfo* data;
    size_t capacity;
    size_t size;
} FileList;

// 模块接口函数声明
void run_code_count();
// 文件查找函数声明
void findAllSubDirsForSourceFiles(const char *path, long *total, FileList* fileList);
// 行数统计函数声明
int countLines(const char *filename);
// 逐行输出函数声明
void typeWriterEffect(const char *text);

#endif // CODE_COUNT_H