// code_count.c
#include "code_count.h"
#include "typewriter.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

// 跨平台头文件处理
#ifdef _WIN32
#include <io.h>
#include <windows.h>
#else
#include <unistd.h>
#include <dirent.h>
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
    #ifdef _WIN32
    strncat(dest, "\\", size-strlen(dest)-1);
    #else
    strncat(dest, "/", size-strlen(dest)-1);
    #endif
    strncat(dest, path2, size-strlen(dest)-1);
}

void addFileToList(FileList* fileList, const char* filename, long line_count)
{
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
        // 限制文件名长度为20字符，确保总长度不超过缓冲区大小
        snprintf(line, sizeof(line), "%-20s %ld lines\n", 
                (strlen(fileList->data[i].filename) > 20) ? "..." : fileList->data[i].filename,
                fileList->data[i].line_count);
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
    sleep(2);
    #endif
    
    // 关闭输出文件
    if (outFile)
    {
        fclose(outFile);
    }
    
    // 释放内存
    free(fileList.data);
}

// 跨平台目录遍历函数
void findAllSubDirsForSourceFiles(const char *path, long *total, FileList* fileList)
{
    char searchPath[MAX];
    #ifdef _WIN32
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
    #else
    DIR* dir;
    struct dirent* entry;
    
    if ((dir = opendir(path)) != NULL) {
        while ((entry = readdir(dir)) != NULL) {
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
                continue;
            }
            
            // 跳过build目录
            if (strcmp(entry->d_name, "build") == 0) {
                continue;
            }
            
            char filePath[MAX];
            safePathConcat(filePath, MAX, path, entry->d_name);
            
            struct stat st;
            if (stat(filePath, &st) == 0 && S_ISDIR(st.st_mode)) {
                findAllSubDirsForSourceFiles(filePath, total, fileList);
            } else {
                const char *ext = strrchr(entry->d_name, '.');
                if (ext && (strcmp(ext, ".c") == 0 || strcmp(ext, ".h") == 0 || 
                            strcmp(ext, ".py") == 0 || strcmp(ext, ".java") == 0 || 
                            strcmp(ext, ".cpp") == 0 || strcmp(ext, ".js") == 0 || 
                            strcmp(ext, ".ts") == 0 || strcmp(ext, ".md") == 0)) {
                    // 跳过CMake相关的文件
                    if (strstr(entry->d_name, "CMake") != NULL) {
                        continue;
                    }
                    
                    int lines = countLines(filePath);
                    *total += lines;
                    addFileToList(fileList, entry->d_name, lines);
                }
            }
        }
        closedir(dir);
    }
    #endif
}

// 实现文件行数统计函数
int countLines(const char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("Failed to open file");
        return 0;
    }

    int count = 0;
    int ch;
    int in_comment = 0;  // 注释处理
    
    // 优化的读取方式
    while ((ch = fgetc(fp)) != EOF) {
        if (!in_comment) {
            if (ch == '\n') {
                count++;
            }
        }
        // 简单的C风格注释处理
        if (ch == '/' && (peekc(fp) == '*')) {
            in_comment = 1;
            fgetc(fp);  // 消耗'*'
        }
        else if (ch == '*' && (peekc(fp) == '/')) {
            in_comment = 0;
            fgetc(fp);  // 消耗'/'
        }
    }
    
    // 处理文件未以换行结尾的情况
    if (ch != '\n' && count > 0) {
        count++;
    }
    
    fclose(fp);
    return count;
}