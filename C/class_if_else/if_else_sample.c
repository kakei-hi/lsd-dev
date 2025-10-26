/*
 * if_else_sample.c - if-else の使い方を説明する簡単なサンプルでござる
 * 初心者向けにコメント多め、関数は短く保つでござる
 */

#include <stdio.h>
#include <stdlib.h>

/* 偶数かどうかを判定する関数でござる（戻り値: 1=偶数, 0=奇数） */
int is_even(int n) {
    /* if-else の基本例でござる */
    if (n % 2 == 0) {
        return 1; /* 偶数でござる */
    } else {
        return 0; /* 奇数でござる */
    }
}

/* 点数に応じて評価文字列を返す関数でござる */
const char *grade_comment(int score) {
    /* 入力チェックを最初に行うでござる */
    if (score < 0 || score > 100) {
        return "無効な点数でござる"; /* 範囲外の値は無効でござる */
    }

    /* if - else if - else の連鎖で段階評価を行うでござる */
    if (score >= 90) {
        return "秀でござる";
    } else if (score >= 80) {
        return "優でござる";
    } else if (score >= 70) {
        return "良でござる";
    } else if (score >= 60) {
        return "可でござる";
    } else {
        return "不可でござる";
    }
}

/* ネストした if の例を示す簡単な関数でござる */
void demonstrate_nested(int a, int b) {
    /* a が正かどうかを確認し、その中で b を判定するでござる */
    if (a > 0) {
        if (b > 0) {
            printf("a と b は共に正でござる\n");
        } else {
            printf("a は正だが b は 0 以下でござる\n");
        }
    } else {
        printf("a は 0 以下でござる\n");
    }
}

/* サンプルの実行用 main 関数でござる */
int main(void) {
    /* is_even のデモンストレーションでござる */
    int n = 5;
    printf("--- if-else の基本例 ---\n");
    printf("数 %d は %s\n", n, is_even(n) ? "偶数" : "奇数");

    /* grade_comment のデモンストレーションでござる */
    printf("\n--- if-else-if の例（評価）---\n");
    int samples[] = {95, 82, 73, 61, 50, -1};
    for (size_t i = 0; i < sizeof(samples)/sizeof(samples[0]); ++i) {
        int s = samples[i];
        printf("点数: %3d -> %s\n", s, grade_comment(s));
    }

    /* ネストした if のデモでござる */
    printf("\n--- ネストした if の例 ---\n");
    demonstrate_nested(3, 4);
    demonstrate_nested(3, -1);
    demonstrate_nested(0, 5);

    return 0; /* 正常終了でござる */
}
