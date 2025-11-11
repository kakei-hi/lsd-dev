/*
 * simple_calculator.c
 * 簡易電卓サンプル
 * - ユーザーが入力する演算子 (+, -, *, /) に応じて
 *   ユーザーが入力する2つの数値 (float) の演算結果を表示する
 * - 不正な演算子の場合は "Invalid operator" を表示する
 *
 * 制約: main 関数のみを使用する
 */

#include <stdio.h>
#include <stdlib.h> /* EXIT_SUCCESS / EXIT_FAILURE を使用 */

/* マジックナンバーを定数化 */
#define OUTPUT_PRECISION 6        /* 小数表示桁数 */
#define EXPECTED_OP_COUNT 1       /* 演算子読み取り数 */
#define EXPECTED_VALUE_COUNT 2    /* 数値読み取り数 */
#define ZERO_FLOAT 0.0f           /* ゼロ判定用 */

int main(void) {
    char op;
    float a, b;

    /* 演算子の入力 */
    printf("演算子を入力してください (+ - * /): ");

    /* 入力成否の検出を追加 */
    if (scanf(" %c", &op) != EXPECTED_OP_COUNT) {
        printf("入力エラー: 演算子を入力してください\n");
        return EXIT_FAILURE;
    }

    /* 値の妥当性検証 */
    if (!(op == '+' || op == '-' || op == '*' || op == '/')) {
        printf("Invalid Operation\n");
        return EXIT_FAILURE;
    }

    /* 2つの数値の入力 */
    printf("2つの数値を入力してください（例: 1.2, 3.4）: ");
    if (scanf("%f, %f", &a, &b) != EXPECTED_VALUE_COUNT) {
        printf("数値の入力エラー\n");
        return EXIT_FAILURE;
    }

    switch (op) {
        case '+':
            printf("%.*f\n", OUTPUT_PRECISION, a + b);
            break;
        case '-':
            printf("%.*f\n", OUTPUT_PRECISION, a - b);
            break;
        case '*':
            printf("%.*f\n", OUTPUT_PRECISION, a * b);
            break;
        case '/':
            if (b == 0.0f) {
                printf("Division by zero\n");
            } else {
                printf("%.*f\n", OUTPUT_PRECISION, a / b);
            }
            break;
    }

    return EXIT_SUCCESS;
}
