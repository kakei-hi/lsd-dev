/*
 * days_in_month.c
 * 西暦 (int) と月 (int) を入力し、その月の日数を表示する簡易プログラム
 * 制約: main 関数のみ使用
 *
 * ルール（閏年判定）:
 *  - 西暦が 400 で割り切れる年は閏年
 *  - 上記以外で 100 で割り切れる年は平年
 *  - それ以外で 4 で割り切れる年は閏年
 */

#include <stdio.h>
#include <stdbool.h>

/* 月の定数定義 */
#define MIN_MONTH 1
#define MAX_MONTH 12

/* 日数の定数定義 */
#define DAYS_31 31
#define DAYS_30 30
#define DAYS_FEB_NORMAL 28
#define DAYS_FEB_LEAP 29

/* 閏年計算用の定数 */
#define YEAR_DIV_400 400
#define YEAR_DIV_100 100
#define YEAR_DIV_4 4

int main(void) {
    int year, month;

    printf("西暦を入力してください（例: 2024）: ");
    if (scanf("%d", &year) != 1) {
        printf("入力エラー: 整数の西暦を入力してください\n");
        return 1;
    }

    printf("月を入力してください（1-12）: ");
    if (scanf("%d", &month) != 1) {
        printf("入力エラー: 整数の月を入力してください\n");
        return 1;
    }

    /* 月の検証 */
    if (month < MIN_MONTH || month > MAX_MONTH) {
        printf("無効な月です: %d\n", month);
        return 1;
    }

    /* 閏年判定 */
    bool is_leap = false;
    if ((year % YEAR_DIV_400) == 0) {
        is_leap = true;
    } else if ((year % YEAR_DIV_100) == 0) {
        is_leap = false;
    } else if ((year % YEAR_DIV_4) == 0) {
        is_leap = true;
    }

    int days;
    switch (month) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            days = DAYS_31;
            break;
        case 4: case 6: case 9: case 11:
            days = DAYS_30;
            break;
        case 2:
            if (is_leap) {
                days = DAYS_FEB_LEAP;
            } else {
                days = DAYS_FEB_NORMAL;
            }
            break;
        default:
            days = 0;
            break;
    }

    printf("%d年%d月は %d 日です\n", year, month, days);

    /* 補足コメント（教育向け）:
     * - 閏年の判定は上のように 400/100/4 の優先順で行うこと
     * - 入力検証 (month の範囲チェック) を忘れないこと
     */

    return 0;
}
