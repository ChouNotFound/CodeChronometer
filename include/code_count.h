#ifndef CODE_COUNT_H
#define CODE_COUNT_H

#include "typewriter.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#ifdef _WIN32
#include <io.h>
#include <windows.h>
#else
#include <unistd.h>
#include <dirent.h>
#endif

#define MAX 1024

typedef struct {
    char filename[256];
    long line_count;
} FileInfo;

typedef struct {
    FileInfo *data;
    size_t size;
    size_t capacity;
} FileList;

void findAllSubDirsForSourceFiles(const char *path, long *total, FileList* fileList);
int countLines(const char *filename);

// 主函数声明
void run_code_count();

#endif // CODE_COUNT_H