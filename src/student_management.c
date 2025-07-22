#ifndef STUDENT_MANAGEMENT_H
#define STUDENT_MANAGEMENT_H

#define MAX_STUDENTS 100  // 鏈€澶у�︾敓鏁伴噺

// 瀹氫箟瀛︾敓缁撴瀯浣�
typedef struct {
    char name[50];
    int id;
    float score;
} Student;

// 鍑芥暟澹版槑
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

// 瀛︾敓鏁扮粍锛岀敤浜庡瓨鍌ㄥ�︾敓淇℃伅
Student students[MAX_STUDENTS];
int student_count = 0;  // 褰撳墠瀛︾敓鏁伴噺

// 娣诲姞瀛︾敓淇℃伅鐨勫嚱鏁板疄鐜�
void add_student() {
    // 濡傛灉瀛︾敓鏁伴噺杈惧埌涓婇檺锛屾彁绀烘棤娉曟坊鍔�
    if (student_count >= MAX_STUDENTS) {
        printf("瀛︾敓鏁伴噺宸茶揪涓婇檺锛屾棤娉曟坊鍔犳洿澶氬�︾敓\n");
        return;
    }
    
    // 杈撳叆瀛︾敓濮撳悕
    printf("璇疯緭鍏ュ�︾敓濮撳悕锛�");
    scanf("%s", students[student_count].name);
    
    // 杈撳叆瀛︾敓瀛﹀彿
    printf("璇疯緭鍏ュ�︾敓瀛﹀彿锛�");
    scanf("%d", &students[student_count].id);
    
    // 杈撳叆瀛︾敓鎴愮哗
    printf("璇疯緭鍏ュ�︾敓鎴愮哗锛�");
    scanf("%f", &students[student_count].score);
    
    // 瀛︾敓鏁伴噺澧炲姞
    student_count++;
    
    printf("瀛︾敓淇℃伅娣诲姞鎴愬姛\n");
}

// 鏄剧ず鎵€鏈夊�︾敓淇℃伅鐨勫嚱鏁板疄鐜�
void display_students() {
    // 濡傛灉娌℃湁瀛︾敓淇℃伅锛屾彁绀烘病鏈夎�板綍
    if (student_count == 0) {
        printf("娌℃湁瀛︾敓淇℃伅\n");
        return;
    }
    
    // 閬嶅巻瀛︾敓鏁扮粍锛屾樉绀哄�︾敓淇℃伅
    printf("鎵€鏈夊�︾敓淇℃伅濡備笅锛歕n");
    for (int i = 0; i < student_count; i++) {
        printf("瀛︾敓 %d:\n", i + 1);
        printf("濮撳悕锛�%s\n", students[i].name);
        printf("瀛﹀彿锛�%d\n", students[i].id);
        printf("鎴愮哗锛�%.2f\n", students[i].score);
        printf("\n");
    }
}

// 鏍规嵁瀛﹀彿鏌ヨ�㈠�︾敓淇℃伅鐨勫嚱鏁板疄鐜�
Student* find_student(int id) {
    // 閬嶅巻瀛︾敓鏁扮粍鏌ユ壘鍖归厤鐨勫�﹀彿
    for (int i = 0; i < student_count; i++) {
        if (students[i].id == id) {
            return &students[i];  // 杩斿洖鎵惧埌鐨勫�︾敓鎸囬拡
        }
    }
    
    return NULL;  // 娌℃湁鎵惧埌杩斿洖NULL
}

// 璁＄畻骞冲潎鎴愮哗鐨勫嚱鏁板疄鐜�
float calculate_average_score() {
    // 濡傛灉娌℃湁瀛︾敓淇℃伅锛岃繑鍥�0
    if (student_count == 0) {
        return 0;
    }
    
    // 璁＄畻鎬绘垚缁�
    float total = 0;
    for (int i = 0; i < student_count; i++) {
        total += students[i].score;
    }
    
    // 杩斿洖骞冲潎鎴愮哗
    return total / student_count;
}

// 鍚�鍔ㄥ�︾敓绠＄悊绯荤粺鐨勫嚱鏁板疄鐜�
void run_student_management() {
    int choice;
    
    while (1) {
        // 鏄剧ず鑿滃崟
        printf("\n瀛︾敓淇℃伅绠＄悊绯荤粺\n");
        printf("1. 娣诲姞瀛︾敓淇℃伅\n");
        printf("2. 鏄剧ず鎵€鏈夊�︾敓淇℃伅\n");
        printf("3. 鏌ヨ�㈠�︾敓淇℃伅\n");
        printf("4. 璁＄畻骞冲潎鎴愮哗\n");
        printf("5. 杩斿洖涓昏彍鍗昞n");
        printf("璇疯緭鍏ヤ綘鐨勯€夋嫨锛�1-5锛夛細");
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
                    printf("璇疯緭鍏ヨ�佹煡璇㈢殑瀛︾敓瀛﹀彿锛�");
                    scanf("%d", &search_id);
                    
                    Student* found = find_student(search_id);
                    if (found != NULL) {
                        printf("鎵惧埌瀛︾敓淇℃伅锛歕n");
                        printf("濮撳悕锛�%s\n", found->name);
                        printf("瀛﹀彿锛�%d\n", found->id);
                        printf("鎴愮哗锛�%.2f\n", found->score);
                    } else {
                        printf("鏈�鎵惧埌瀛﹀彿涓� %d 鐨勫�︾敓\n", search_id);
                    }
                    break;
                }
            case 4:
                {
                    float average = calculate_average_score();
                    if (student_count > 0) {
                        printf("褰撳墠瀛︾敓鐨勫钩鍧囨垚缁╀负锛�%.2f\n", average);
                    } else {
                        printf("娌℃湁瀛︾敓淇℃伅锛屾棤娉曡�＄畻骞冲潎鎴愮哗\n");
                    }
                    break;
                }
            case 5:
                printf("杩斿洖涓昏彍鍗昞n");
                return;
            default:
                printf("鏃犳晥鐨勯€夋嫨锛岃�疯緭鍏�1-5涔嬮棿鐨勬暟瀛梊n");
        }
    }
}