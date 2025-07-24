// typewriter.c
#include "typewriter.h"
#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

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