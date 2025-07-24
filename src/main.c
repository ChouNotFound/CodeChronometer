// main.c
#include "code_count.h"
#include "typewriter.h"
#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
#include <conio.h>  // Windows平台需要_conio.h头文件
#else
#include <unistd.h>
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
        (void)scanf("%d", &choice);
        
        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        switch (choice) 
        {
            case 1:
                {
                // 添加路径选择逻辑
                typeWriterEffect("\nChoose path option:\n");
                typeWriterEffect("1. Current directory\n");
                typeWriterEffect("2. Custom path\n");
                typeWriterEffect("Enter your choice (1-2): ");
                
                int path_choice;
                (void)scanf("%d", &path_choice);
                
                while ((c = getchar()) != '\n' && c != EOF);
                
                char path[1024] = ".."; // 默认路径
                
                if (path_choice == 2) {
                    typeWriterEffect("\nEnter custom path: ");
                    (void)fgets(path, sizeof(path), stdin);
                    // 移除末尾换行符
                    path[strcspn(path, "\n")] = '\0';
                }
                
                typeWriterEffect("\nDo you want to generate a report? (y/n): ");
                char report_choice;
                (void)scanf(" %c", &report_choice);
                if (report_choice == 'y' || report_choice == 'Y') 
                {
                    generate_report();
                }
                
                // 执行代码统计，使用选择的路径
                run_code_count(path);
                
                // 统计结束后显示感谢信息并等待退出
                typeWriterEffect("\nThank you for using this program. Goodbye!");
                #ifdef _WIN32
                _getch();
                #else
                getchar();
                #endif
                return 0; // 直接退出程序
                }
            
            case 2:
                typeWriterEffect("\nThank you for using this program. Goodbye!");
                #ifdef _WIN32
                // 先等待按键再退出
                _getch();
                #else
                getchar();
                #endif
                return 0;
            
            default:
                typeWriterEffect("\nInvalid choice. Please enter a number between 1 and 2\n");
        }
    }
    
    return 0;
}
