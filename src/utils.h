#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdarg.h>

// 打字机效果输出字符串
void typeWriterEffect(const char* str);

// 格式化打字机效果输出
void typeWriterPrintf(const char* format, ...);

// 通用输入验证函数
int get_valid_input(double *value);

#endif // UTILS_H