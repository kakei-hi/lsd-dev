/*
 * vowel_check.c
 * ユーザーが入力した1文字（char）を判定して、母音か子音かを表示するサンプル
 * 制約: main 関数のみを使用（他の関数は作らない）
 *
 * 使い方（実行時に1文字を入力）:
 *   $ ./vowel_check
 *   文字を1つ入力してください: a
 *   入力: 'a' -> 母音です
 *
 * 備考:
 *  - 小文字の英字のみ判定（'a','i','u','e','o' を母音とする）
 *  - サンプルの簡潔さを優先しており、大文字や非英字の扱いは教示コメントで補足
 */

#include <stdio.h>
#include <stdlib.h>  /* EXIT_SUCCESS, EXIT_FAILURE のため */
#include <ctype.h>   /* isalpha() のため */

/* 定数定義 */
#define INPUT_SUCCESS 1

int main(void) {
    char input_char;  /* より説明的な変数名に変更 */

    printf("文字を1つ入力してください: ");
    
    /* 入力処理と検証 */
    if (scanf(" %c", &input_char) != INPUT_SUCCESS) {
        printf("入力エラー: 1文字を入力してください\n");
        return EXIT_FAILURE;
    }

    /* 英字であることを確認 */
    if (!isalpha(input_char)) {
        printf("エラー: '%c' は英字ではありません\n", input_char);
        return EXIT_FAILURE;
    }

    /* 判定処理: 小文字の母音かどうかを判定 */
    switch (tolower(input_char)) {  /* 大文字も受け付けるように改善 */
        case 'a':
        case 'i':
        case 'u':
        case 'e':
        case 'o':
            printf("入力: '%c' -> 母音です\n", input_char);
            break;
        default:
            printf("入力: '%c' -> 子音です\n", input_char);
            break;
    }

    return EXIT_SUCCESS;
}
