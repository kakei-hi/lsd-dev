/*
 *
 *	多次元配列　点数一覧
 *
 */

#include <stdio.h>

// 定数定義
#define STUDENT_COUNT 5      // 学生の人数
#define SUBJECT_COUNT 5      // 科目の数
#define COLUMN_COUNT 6       // 列数（学生番号 + 科目数）
#define STUDENT_ID_INDEX 0   // 学生番号の列インデックス
#define FIRST_SUBJECT_INDEX 1 // 最初の科目の列インデックス

int main(void)
{
    // 成績データの初期化
    // [学生][項目] 項目: 0=学生番号, 1=英語, 2=数学, 3=国語, 4=理科, 5=社会
    int scores[STUDENT_COUNT][COLUMN_COUNT] = {
        {1010, 80, 55, 92, 71, 81},
        {1032, 62, 54, 67, 75, 78},
        {1084, 52, 42, 52, 60, 59},
        {1107, 83, 91, 85, 96, 88},
        {1116, 72, 73, 80, 69, 65}
    };
    
    float average_by_subject[SUBJECT_COUNT];  // 科目毎の平均点
    float average_by_student[STUDENT_COUNT];  // 学生毎の平均点
    int i, j;
    float sum;
    
    // ========================================
    // 学生毎の平均点を計算する
    // ========================================
    for (i = 0; i < STUDENT_COUNT; i++) {
        sum = 0.0;
        
        // 各科目の得点を合計（学生番号を除く）
        for (j = FIRST_SUBJECT_INDEX; j < COLUMN_COUNT; j++) {
            sum += (float)scores[i][j];
        }
        
        // 平均点を計算（5科目で割る）
        average_by_student[i] = sum / SUBJECT_COUNT;
    }
    
    // ========================================
    // 科目毎の平均点を計算する
    // ========================================
    for (i = FIRST_SUBJECT_INDEX; i < COLUMN_COUNT; i++) {
        sum = 0.0;
        
        // 全学生の該当科目の得点を合計
        for (j = 0; j < STUDENT_COUNT; j++) {
            sum += (float)scores[j][i];
        }
        
        // 平均点を計算（5人で割る）
        // 科目インデックスと配列インデックスのズレを調整
        average_by_subject[i - FIRST_SUBJECT_INDEX] = sum / STUDENT_COUNT;
    }
    
    // ========================================
    // 結果を表示する
    // ========================================
    
    // ヘッダー行の表示
    printf("\n学生番号\t英語\t\t数学\t\t国語\t\t理科\t\t社会\t\t平均点\n");
    
    // 各学生の成績と平均点を表示
    for (i = 0; i < STUDENT_COUNT; i++) {
        // 学生番号と各科目の得点を表示
        for (j = 0; j < COLUMN_COUNT; j++) {
            printf("%d\t\t", scores[i][j]);
        }
        // 平均点を表示（小数点以下2桁）
        printf("%.2f\n", average_by_student[i]);
    }
    
    // 区切り線の表示
    printf("-----------------------------------------------------------------------------------------------------\n");
    
    // 科目毎の平均点を表示
    printf("\t\t");
    for (i = 0; i < SUBJECT_COUNT; i++) {
        printf("%.2f\t\t", average_by_subject[i]);
    }
    printf("\n");
    
    return 0;
}


