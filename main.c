// main.c
#include "student_management.h"
#include "code_count.h"  // 引入code_count功能的头文件

int main() {
    int choice;
    
    while (1) {
        // 显示主菜单
        printf("\n=== 主菜单 ===\n");
        printf("1. 学生信息管理系统\n");
        printf("2. 文件统计功能\n");
        printf("3. 退出程序\n");
        printf("请输入你的选择（1-3）：");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                // 调用学生管理系统
                run_student_management();
                break;
            case 2:
                // 调用代码统计功能
                run_code_count();
                break;
            case 3:
                printf("感谢使用本程序，再见！\n");
                return 0;
            default:
                printf("无效的选择，请输入1-3之间的数字\n");
        }
    }
    
    return 0;
}