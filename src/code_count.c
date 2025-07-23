// code_count.c
#include "code_count.h"
#include "typewriter.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>
#include <errno.h>

// 跨平台头文件处理
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

// 宏定义
#define MAX 1024

// 函数声明
void findAllSubDirsForSourceFiles(const char *path, long *total, FileList* fileList);
int countLines(const char *filename);

// 辅助函数声明
static int peekc(FILE *fp);
static void safePathConcat(char *dest, size_t size, const char *path1, const char *path2);
static void addFileToList(FileList* fileList, const char* filename, long line_count);
static void printFileList(const FileList* fileList, FILE* outFile);

// 辅助函数实现
int peekc(FILE *fp) 
{
    int ch = fgetc(fp);
    ungetc(ch, fp);
    return ch;
}

void safePathConcat(char *dest, size_t size, const char *path1, const char *path2) 
{
    strncpy(dest, path1, size-1);
    strncat(dest, "\\", size-strlen(dest)-1);
    strncat(dest, path2, size-strlen(dest)-1);
}

void addFileToList(FileList* fileList, const char* filename, long line_count) {
    if (fileList->size >= fileList->capacity) {
        fileList->capacity = fileList->capacity == 0 ? 4 : fileList->capacity * 2;
        fileList->data = realloc(fileList->data, fileList->capacity * sizeof(FileInfo));
    }
    strncpy(fileList->data[fileList->size].filename, filename, 255);
    fileList->data[fileList->size].line_count = line_count;
    fileList->size++;
}

void printFileList(const FileList* fileList, FILE* outFile)
{
    for (size_t i = 0; i < fileList->size; i++)
    {
        char line[100];
        snprintf(line, sizeof(line), "%-30s %ld lines\n", fileList->data[i].filename, fileList->data[i].line_count);
        typeWriterEffect(line);
        if (outFile)
        {
            fprintf(outFile, "%s", line);
        }
    }
}


// 主函数
void run_code_count()
{
    long total = 0;
    FileList fileList = {0};
    
    // 打开输出文件
    FILE* outFile = fopen("code_stats.txt", "w");
    if (!outFile)
    {
        typeWriterEffect("Warning: 无法创建输出文件\n");
    }
    
    // 递归查找源文件
    findAllSubDirsForSourceFiles("..", &total, &fileList);
    
    // 打印标题
    typeWriterEffect("\n=== Code Statistics Report ===\n");
    if (outFile)
    {
        fprintf(outFile, "=== Code Statistics Report ===\n");
    }
    
    // 打印文件列表
    printFileList(&fileList, outFile);
    
    typeWriterEffect("------------------------\n");
    if (outFile)
    {
        fprintf(outFile, "------------------------\n");
    }
    
    char total_line[50];
    snprintf(total_line, sizeof(total_line), "Total: %ld lines\n", total);
    typeWriterEffect(total_line);
    if (outFile)
    {
        fprintf(outFile, "%s", total_line);
    }
    
    // 等待2秒
    #ifdef _WIN32
    Sleep(2000);
    #else
    usleep(2000000);
    #endif
    
    // 释放内存
    free(fileList.data);
    
    // 关闭输出文件
    if (outFile)
    {
        fclose(outFile);
    }
}

// Windows特有的文件查找函数
void findAllSubDirsForSourceFiles(const char *path, long *total, FileList* fileList) {
    char searchPath[MAX];
    struct _finddata_t fileinfo;
    intptr_t handle;
    
    safePathConcat(searchPath, MAX, path, "*");
    
    if ((handle = _findfirst(searchPath, &fileinfo)) != -1) {
        do {
            if (strcmp(fileinfo.name, ".") == 0 || strcmp(fileinfo.name, "..") == 0) {
                continue;
            }
            
            // 跳过build目录
            if (strcmp(fileinfo.name, "build") == 0) {
                continue;
            }
            
            char filePath[MAX];
            safePathConcat(filePath, MAX, path, fileinfo.name);
            
            if (fileinfo.attrib & _A_SUBDIR) {
                findAllSubDirsForSourceFiles(filePath, total, fileList);
            } else {
                const char *ext = strrchr(fileinfo.name, '.');
                if (ext && (strcmp(ext, ".c") == 0 || strcmp(ext, ".h") == 0 || 
                            strcmp(ext, ".py") == 0 || strcmp(ext, ".java") == 0 || 
                            strcmp(ext, ".cpp") == 0 || strcmp(ext, ".js") == 0 || 
                            strcmp(ext, ".ts") == 0 || strcmp(ext, ".md") == 0)) {
                    // 跳过CMake相关的文件
                    if (strstr(fileinfo.name, "CMake") != NULL) {
                        continue;
                    }
                    
                    int lines = countLines(filePath);
                    *total += lines;
                    addFileToList(fileList, fileinfo.name, lines);
                }
            }
        } while (_findnext(handle, &fileinfo) == 0);
        
        _findclose(handle);
    }
}

// Implement file line counting function
int countLines(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("Failed to open file");
        return 0;
    }

    int count = 0;
    int ch;
    int in_comment = 0;  // Comment handling
    
    // Optimized reading approach
    while ((ch = fgetc(fp)) != EOF) {
        if (!in_comment) {
            if (ch == '\n') {
                count++;
            }
        }
        // Simple C-style comment handling
        if (ch == '/' && (peekc(fp) == '*')) {
            in_comment = 1;
            fgetc(fp);  // consume '*'
        }
        else if (ch == '*' && (peekc(fp) == '/')) {
            in_comment = 0;
            fgetc(fp);  // consume '/'
        }
    }
    
    // Handle case where file ends without a newline
    if (ch != '\n' && count > 0) {
        count++;
    }
    
    fclose(fp);
    return count;
}
