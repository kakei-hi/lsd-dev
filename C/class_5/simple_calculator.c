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

int main(void) {
    char op;
    float a, b;

    /* 演算子の入力 */
    printf("演算子を入力してください (+ - * /): ");
    if (scanf(" %c", &op) != 1) {
        printf("入力エラー\n");
        return 1;
    }

    /* 2つの数値の入力 */
    printf("2つの数値を入力してください（例: 1.2 3.4）: ");
    if (scanf("%f %f", &a, &b) != 2) {
        printf("数値の入力エラー\n");
        return 1;
    }

    switch (op) {
        case '+':
            printf("%.6f\n", a + b);
            break;
        case '-':
            printf("%.6f\n", a - b);
            break;
        case '*':
            printf("%.6f\n", a * b);
            break;
        case '/':
            if (b == 0.0f) {
                printf("Division by zero\n");
            } else {
                printf("%.6f\n", a / b);
            }
            break;
        default:
            printf("Invalid operator\n");
            break;
    }

    return 0;
}
