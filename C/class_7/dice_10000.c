/*
 * dice_10000.c
 * サイコロを10000回振り，1の目が出た回数を数える（配列は使用しない）
 * main関数のみで実装。終了ステイタスに EXIT_SUCCESS / EXIT_FAILURE を使用する。
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    /* 試行回数は定数として定義 */
    const int trials = 10000;

    /* 1の目の出現回数を数える（配列は使用しない） */
    int count_one = 0;

    /* 乱数初期化用のシード取得 */
    time_t seed = time(NULL);
    if (seed == (time_t)-1) {
        /* 時刻取得に失敗したらエラー終了 */
        printf("time() failed\n");
        return EXIT_FAILURE;
    }

    /* シードで srand を初期化（unsigned int にキャスト） */
    srand((unsigned int)seed);

    /* サイコロを trials 回振る */
    for (int i = 0; i < trials; ++i) {
        /* 1〜6 のランダムな値を生成 */
        int roll = (rand() % 6) + 1;
        if (roll == 1) {
            ++count_one;
        }
    }

    /* 結果を出力 */
    printf("サイコロを%d回振り，1の目が出た回数: %d\n", trials, count_one);

    return EXIT_SUCCESS;
}
