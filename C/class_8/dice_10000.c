/*
 * dice_10000.c
 * 1の目が10000回出るまでサイコロを振り，総試行回数を数える（配列は使用しない）
 * main関数のみで実装。終了ステイタスに EXIT_SUCCESS / EXIT_FAILURE を使用する。
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    /* 目標とする1の目の出現回数を定数として定義 */
    const int target_count = 10000;

    /* 1の目の出現回数を数える */
    int count_one = 0;
    
    /* サイコロを振った総回数を数える */
    int total_trials = 0;

    /* 乱数初期化用のシード取得 */
    time_t seed = time(NULL);
    if (seed == (time_t)-1) {
        /* 時刻取得に失敗したらエラー終了 */
        printf("time() failed\n");
        return EXIT_FAILURE;
    }

    /* シードで srand を初期化（unsigned int にキャスト） */
    srand((unsigned int)seed);

    /* 1の目が target_count 回出るまでサイコロを振る */
    while (count_one < target_count) {
        /* 1〜6 のランダムな値を生成 */
        int roll = (rand() % 6) + 1;
        total_trials++;
        
        if (roll == 1) {
            count_one++;
        }
    }

    /* 結果を出力 */
    printf("1の目が%d回出るまでにサイコロを振った回数: %d\n", target_count, total_trials);

    return EXIT_SUCCESS;
}
