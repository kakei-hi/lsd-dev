/*
 * exercise10_1.c
 * 文字列の長さを2つの方法で計算する
 * 1. strlen関数を使う方法
 * 2. 手動でカウントする方法
 */

#include <stdio.h>
#include <string.h>

// 定数定義
#define STRING_COUNT 3      // 文字列の個数
#define MAX_STRING_LEN 5    // 各文字列の最大長

int main(void)
{
    // 文字列配列の初期化
    char str2[STRING_COUNT][MAX_STRING_LEN] = {{"XYZ"}, {"12"}, {"*+?!"}};
    int i;      // ループカウンタ（文字列のインデックス）
    int j;      // ループカウンタ（文字のインデックス）

    // 方法1: strlen関数を使った文字数カウント
    printf("=== strlen関数を使った文字数カウント ===\n");
    for (i = 0; i < STRING_COUNT; i++) {
        printf("\"%s\"の文字数は%lu文字です\n", 
               str2[i], strlen(str2[i]));
    }

    // 方法2: 手動で文字数をカウント
    printf("\n=== 手動で文字数をカウント ===\n");
    for (i = 0; i < STRING_COUNT; i++) {
        // NULL文字まで数える
        j = 0;
        while (str2[i][j] != '\0') {
            j++;
        }
        printf("\"%s\"の文字数は%d文字です\n", str2[i], j);
    }

    return 0;
}
