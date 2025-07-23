// main.c
#include "code_count.h"
#include "typewriter.h"
#include <stdio.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>  // 添加Linux下的usleep支持
#endif

int main() 
{
    while (1) 
    {
        typeWriterEffect("\n=== Code Statistics System ===\n");
        typeWriterEffect("1. Run code statistics\n");
        typeWriterEffect("2. Exit\n");
        typeWriterEffect("Enter your choice (1-2): ");
        
        int choice;
        (void)scanf("%d", &choice);  // 显式忽略scanf返回值
        
        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        switch (choice) {
            case 1:
                run_code_count();
                break;
            case 2:
                typeWriterEffect("\nThank you for using this program. Goodbye!\n");
                #ifdef _WIN32
                Sleep(1000);
                #else
                usleep(1000000);
                #endif
                return 0;
            case 3:
                typeWriterEffect("\nInvalid choice. Please enter a number between 1 and 2\n");
        }
    }
    
    return 0;
}
