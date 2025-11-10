/***********************
 *  九九一覧表
 * ********************/

#include <stdio.h>
#include <stdlib.h>

/* 九九の範囲定数 */
#define MULTIPLICATION_MIN 1
#define MULTIPLICATION_MAX 9

/* 表示用のフォーマット定数 */
#define DISPLAY_DIGITS 2

/**
 * メイン関数: 九九表全体を表示
 */
int main(void) {
    int row, col;

    /* ヘッダー（列番号）を表示 */
    printf("\t");   // 左上の空白用タブ
    for (col = MULTIPLICATION_MIN; col <= MULTIPLICATION_MAX; col++) {
        printf("%*d\t", DISPLAY_DIGITS, col);
    }
    printf("\n\n");

    /* 九九表の本体（各行の計算結果）を表示 */
    for (row = MULTIPLICATION_MIN; row <= MULTIPLICATION_MAX; row++) {
        printf("%*d", DISPLAY_DIGITS, row);    // 行番号を表示
        for (col = MULTIPLICATION_MIN; col <= MULTIPLICATION_MAX; col++) {
            printf("\t%*d", DISPLAY_DIGITS, row * col);
        }
        printf("\n");
    }
    
    return EXIT_SUCCESS;
}
