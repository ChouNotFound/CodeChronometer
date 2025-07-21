#ifndef STUDENT_MANAGEMENT_H
#define STUDENT_MANAGEMENT_H

#define MAX_STUDENTS 100  // 最大学生数量

// 定义学生结构体
typedef struct {
    char name[50];
    int id;
    float score;
} Student;

// 函数声明
void add_student();
void display_students();
Student* find_student(int id);
float calculate_average_score();
void run_student_management();

#endif // STUDENT_MANAGEMENT_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student_management.h"

// 学生数组，用于存储学生信息
Student students[MAX_STUDENTS];
int student_count = 0;  // 当前学生数量

// 添加学生信息的函数实现
void add_student() {
    // 如果学生数量达到上限，提示无法添加
    if (student_count >= MAX_STUDENTS) {
        printf("学生数量已达上限，无法添加更多学生\n");
        return;
    }
    
    // 输入学生姓名
    printf("请输入学生姓名：");
    scanf("%s", students[student_count].name);
    
    // 输入学生学号
    printf("请输入学生学号：");
    scanf("%d", &students[student_count].id);
    
    // 输入学生成绩
    printf("请输入学生成绩：");
    scanf("%f", &students[student_count].score);
    
    // 学生数量增加
    student_count++;
    
    printf("学生信息添加成功\n");
}

// 显示所有学生信息的函数实现
void display_students() {
    // 如果没有学生信息，提示没有记录
    if (student_count == 0) {
        printf("没有学生信息\n");
        return;
    }
    
    // 遍历学生数组，显示学生信息
    printf("所有学生信息如下：\n");
    for (int i = 0; i < student_count; i++) {
        printf("学生 %d:\n", i + 1);
        printf("姓名：%s\n", students[i].name);
        printf("学号：%d\n", students[i].id);
        printf("成绩：%.2f\n", students[i].score);
        printf("\n");
    }
}

// 根据学号查询学生信息的函数实现
Student* find_student(int id) {
    // 遍历学生数组查找匹配的学号
    for (int i = 0; i < student_count; i++) {
        if (students[i].id == id) {
            return &students[i];  // 返回找到的学生指针
        }
    }
    
    return NULL;  // 没有找到返回NULL
}

// 计算平均成绩的函数实现
float calculate_average_score() {
    // 如果没有学生信息，返回0
    if (student_count == 0) {
        return 0;
    }
    
    // 计算总成绩
    float total = 0;
    for (int i = 0; i < student_count; i++) {
        total += students[i].score;
    }
    
    // 返回平均成绩
    return total / student_count;
}

// 启动学生管理系统的函数实现
void run_student_management() {
    int choice;
    
    while (1) {
        // 显示菜单
        printf("\n学生信息管理系统\n");
        printf("1. 添加学生信息\n");
        printf("2. 显示所有学生信息\n");
        printf("3. 查询学生信息\n");
        printf("4. 计算平均成绩\n");
        printf("5. 返回主菜单\n");
        printf("请输入你的选择（1-5）：");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                add_student();
                break;
            case 2:
                display_students();
                break;
            case 3:
                {
                    int search_id;
                    printf("请输入要查询的学生学号：");
                    scanf("%d", &search_id);
                    
                    Student* found = find_student(search_id);
                    if (found != NULL) {
                        printf("找到学生信息：\n");
                        printf("姓名：%s\n", found->name);
                        printf("学号：%d\n", found->id);
                        printf("成绩：%.2f\n", found->score);
                    } else {
                        printf("未找到学号为 %d 的学生\n", search_id);
                    }
                    break;
                }
            case 4:
                {
                    float average = calculate_average_score();
                    if (student_count > 0) {
                        printf("当前学生的平均成绩为：%.2f\n", average);
                    } else {
                        printf("没有学生信息，无法计算平均成绩\n");
                    }
                    break;
                }
            case 5:
                printf("返回主菜单\n");
                return;
            default:
                printf("无效的选择，请输入1-5之间的数字\n");
        }
    }
}