/*
 * if_vs_switch.c - if文とswitch文の使い分けを説明するサンプルでござる
 * 年齢確認（if文）と色選択（switch文）を例に使い分けを示すでござる
 */

#include <stdio.h>

int main(void) {
    /* 年齢による判定: if文が適している例でござる */
    int age = 15;    /* 年齢でござる */
    int has_id = 0;  /* 身分証の有無でござる（0: なし, 1: あり）*/
    
    printf("=== 映画の年齢制限判定 (if文の例) ===\n");
    printf("お客様の年齢: %d歳\n", age);
    printf("身分証明書: %s\n", has_id ? "あり" : "なし");

    /* if文の例：複数条件の組み合わせと範囲判定でござる */
    if (age < 0) {
        printf("エラー: 無効な年齢でござる\n");
    } else if (age >= 18) {
        printf("R18映画：視聴可能でござる\n");
    } else if (age >= 15 && has_id) {
        printf("PG15映画：身分証確認で視聴可能でござる\n");
    } else if (age >= 12) {
        printf("PG12映画：視聴可能でござる\n");
    } else {
        printf("子供向け映画のみ視聴可能でござる\n");
    }

    /* 色選択: switch文が適している例でござる */
    char color = 'R';  /* 選択された色コードでござる */
    
    printf("\n=== 選択された色の表示 (switch文の例) ===\n");
    printf("色コード: %c\n", color);
    
    /* switch文の例：文字による単純な分岐でござる */
    printf("選択された色は");
    switch (color) {
        case 'R':
            printf("赤でござる\n");
            break;
        case 'G':
            printf("緑でござる\n");
            break;
        case 'B':
            printf("青でござる\n");
            break;
        case 'Y':
            printf("黄でござる\n");
            break;
        default:
            printf("未定義の色でござる\n");
            break;
    }

    /* 季節の催し物: 両方の実装を比較するでござる */
    int month = 4;  /* 月でござる */
    printf("\n=== 季節の催し物案内 (両方の実装比較) ===\n");
    printf("現在の月: %d月\n", month);

    /* if文での実装：範囲判定でござる */
    printf("if文による案内 -> ");
    if (month >= 3 && month <= 5) {
        printf("春の花見でござる\n");
    } else if (month >= 6 && month <= 8) {
        printf("夏祭りでござる\n");
    } else if (month >= 9 && month <= 11) {
        printf("紅葉狩りでござる\n");
    } else if (month == 12 || month == 1 || month == 2) {
        printf("冬のイルミネーションでござる\n");
    } else {
        printf("無効な月でござる\n");
    }

    /* switch文での実装：月ごとの分類でござる */
    printf("switch文による案内 -> ");
    switch (month) {
        case 3:
        case 4:
        case 5:
            printf("春の花見でござる\n");
            break;
        case 6:
        case 7:
        case 8:
            printf("夏祭りでござる\n");
            break;
        case 9:
        case 10:
        case 11:
            printf("紅葉狩りでござる\n");
            break;
        case 12:
        case 1:
        case 2:
            printf("冬のイルミネーションでござる\n");
            break;
        default:
            printf("無効な月でござる\n");
            break;
    }

    /*
     * 使い分けの要点でござる：
     *
     * if文を使う場面：
     * 1. 範囲の判定（年齢制限など）でござる
     * 2. 複数の条件を組み合わせる場合（年齢と身分証など）でござる
     * 3. 条件が複雑な場合でござる
     *
     * switch文を使う場面：
     * 1. 単一の値で分岐する場合（色コードなど）でござる
     * 2. 値が限定されている場合でござる
     * 3. fall-through（意図的なbreak省略）を使う場合でござる
     */

    return 0;
}
