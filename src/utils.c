// utils.c
#include "utils.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#define OUTPUT_DELAY_MS 10

// 打字机效果输出字符串
void typeWriterEffect(const char* str) 
{
    while (*str) 
    {
        putchar(*str++);
        fflush(stdout);
        #ifdef _WIN32
        Sleep(OUTPUT_DELAY_MS);
        #else
        usleep(OUTPUT_DELAY_MS * 1000);
        #endif
    }
}

// 格式化打字机效果输出
void typeWriterPrintf(const char* format, ...) 
{
    va_list args;
    va_start(args, format);
    
    char buffer[1024];
    vsnprintf(buffer, sizeof(buffer), format, args);
    
    va_end(args);
    
    typeWriterEffect(buffer);
}

// 通用输入验证函数
int get_valid_input(int *value) 
{
    while(1) 
    {
        if(scanf("%d", value) == 1) 
        {
            // 清除可能的多余输入
            int c;
            while((c = getchar()) != '\n' && c != EOF);
            return 1;
        } 
        else 
        {
            // 清除无效输入
            int c;
            while((c = getchar()) != '\n' && c != EOF);
            typeWriterPrintf("\n输入无效，请输入整数：");
        }
    }
}
