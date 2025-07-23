// typewriter.c
#include "typewriter.h"
#include <stdio.h>
#include <windows.h>

void typeWriterEffect(const char *text) 
{
    while (*text) 
    {
        putchar(*text++);
        fflush(stdout);
        Sleep(OUTPUT_DELAY_MS);
    }
}
