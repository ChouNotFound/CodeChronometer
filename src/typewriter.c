// typewriter.c
#include "typewriter.h"
#include <stdio.h>
#include <unistd.h>  // 鏇挎崲windows.h涓簆osix鏍囧噯澶存枃浠�

void typeWriterEffect(const char* str) {
    while (*str) {
        putchar(*str++);
        fflush(stdout);
        usleep(10000);  // 缁熶竴浣跨敤usleep瀹炵幇璺ㄥ钩鍙板欢杩�
    }
}