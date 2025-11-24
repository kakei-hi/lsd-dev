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

/*
 * 関数: calculate_student_average
 * 目的: 指定した学生の平均点を計算する
 * 引数: scores - 成績データ配列, student_index - 学生のインデックス
 * 戻り値: その学生の平均点
 */
float calculate_student_average(int scores[][COLUMN_COUNT], int student_index)
{
    float sum = 0.0;
    
    // 各科目の得点を合計（学生番号を除く）
    for (int j = FIRST_SUBJECT_INDEX; j < COLUMN_COUNT; j++) {
        sum += (float)scores[student_index][j];
    }
    
    return sum / SUBJECT_COUNT;
}

/*
 * 関数: calculate_subject_average
 * 目的: 指定した科目の平均点を計算する
 * 引数: scores - 成績データ配列, subject_index - 科目のインデックス
 * 戻り値: その科目の平均点
 */
float calculate_subject_average(int scores[][COLUMN_COUNT], int subject_index)
{
    float sum = 0.0;
    
    // 全学生の該当科目の得点を合計
    for (int i = 0; i < STUDENT_COUNT; i++) {
        sum += (float)scores[i][subject_index];
    }
    
    return sum / STUDENT_COUNT;
}

/*
 * 関数: calculate_all_student_averages
 * 目的: 全学生の平均点を計算する
 * 引数: scores - 成績データ配列, averages - 平均点を格納する配列
 */
void calculate_all_student_averages(int scores[][COLUMN_COUNT], float averages[])
{
    for (int i = 0; i < STUDENT_COUNT; i++) {
        averages[i] = calculate_student_average(scores, i);
    }
}

/*
 * 関数: calculate_all_subject_averages
 * 目的: 全科目の平均点を計算する
 * 引数: scores - 成績データ配列, averages - 平均点を格納する配列
 */
void calculate_all_subject_averages(int scores[][COLUMN_COUNT], float averages[])
{
    for (int i = FIRST_SUBJECT_INDEX; i < COLUMN_COUNT; i++) {
        // 科目インデックスと配列インデックスのズレを調整
        averages[i - FIRST_SUBJECT_INDEX] = calculate_subject_average(scores, i);
    }
}

/*
 * 関数: print_header
 * 目的: 成績表のヘッダーを表示する
 */
void print_header(void)
{
    printf("\n学生番号\t英語\t\t数学\t\t国語\t\t理科\t\t社会\t\t平均点\n");
}

/*
 * 関数: print_student_scores
 * 目的: 各学生の成績と平均点を表示する
 * 引数: scores - 成績データ配列, averages - 学生毎の平均点配列
 */
void print_student_scores(int scores[][COLUMN_COUNT], float averages[])
{
    for (int i = 0; i < STUDENT_COUNT; i++) {
        // 学生番号と各科目の得点を表示
        for (int j = 0; j < COLUMN_COUNT; j++) {
            printf("%d\t\t", scores[i][j]);
        }
        // 平均点を表示（小数点以下2桁）
        printf("%.2f\n", averages[i]);
    }
}

/*
 * 関数: print_subject_averages
 * 目的: 各科目の平均点を表示する
 * 引数: averages - 科目毎の平均点配列
 */
void print_subject_averages(float averages[])
{
    printf("-----------------------------------------------------------------------------------------------------\n");
    printf("\t\t");
    
    for (int i = 0; i < SUBJECT_COUNT; i++) {
        printf("%.2f\t\t", averages[i]);
    }
    printf("\n");
}

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
    
    // 学生毎の平均点を計算
    calculate_all_student_averages(scores, average_by_student);
    
    // 科目毎の平均点を計算
    calculate_all_subject_averages(scores, average_by_subject);
    
    // 結果を表示
    print_header();
    print_student_scores(scores, average_by_student);
    print_subject_averages(average_by_subject);
    
    return 0;
}


