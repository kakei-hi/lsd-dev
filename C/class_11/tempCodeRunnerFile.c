/*
 *
 *	外貨換算
 *
 */

#include <stdio.h>
#include <stdlib.h>

void clear_input_buffer(void);
void calculate_foreign_amounts(float amount_yen,
                               float rate_yen_per_usd,
                               float rate_yen_per_euro,
                               float *amount_usd,
                               float *amount_euro);

int main ()
{
    // 入出力用の変数（意味のある名前に変更）
    float amount_yen, amount_usd, amount_euro;
    float rate_yen_per_usd, rate_yen_per_euro;

    printf("\n為替レートを入力してください");
    printf("\n対米ドル（円/米ドル）\t");
    if (scanf("%f", &rate_yen_per_usd) != 1 || rate_yen_per_usd <= 0.0f) {
        clear_input_buffer();
        printf("\n入力エラー：対米ドルレートは正の数値で入力してください\n");
        return EXIT_FAILURE;
    }
    clear_input_buffer();

    printf("\n対ユーロ（円/ユーロ）\t");
    if (scanf("%f", &rate_yen_per_euro) != 1 || rate_yen_per_euro <= 0.0f) {
        clear_input_buffer();
        printf("\n入力エラー：対ユーロレートは正の数値で入力してください\n");
        return EXIT_FAILURE;
    }
    clear_input_buffer();

    printf("\n換算金額（円）を入力してください\t");
    if (scanf("%f", &amount_yen) != 1 || amount_yen < 0.0f) {
        clear_input_buffer();
        printf("\n入力エラー：金額は0以上の数値で入力してください\n");
        return EXIT_FAILURE;
    }
    clear_input_buffer();

    // 円から外貨へ換算
    calculate_foreign_amounts(amount_yen,
                              rate_yen_per_usd,
                              rate_yen_per_euro,
                              &amount_usd,
                              &amount_euro);

    printf("\n%.2f円は%.2f米ドル，%.2fユーロです", amount_yen, amount_usd, amount_euro);
    printf("\n");

    return EXIT_SUCCESS;
}

// 入力バッファをクリアして scanf の二重入力問題を回避
void clear_input_buffer(void)
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {
        // 入力行の残りを破棄
    }
}

// 外貨換算
// 与えられた金額（円）および為替レート（円/米ドル，円/ユーロ）から
// 外貨金額（米ドル，ユーロ）を計算する
void calculate_foreign_amounts(float amount_yen,
                               float rate_yen_per_usd,
                               float rate_yen_per_euro,
                               float *amount_usd,
                               float *amount_euro)
{
    // NULLポインタ安全性のためのチェック
    if (amount_usd == NULL || amount_euro == NULL) {
        return;
    }

    // レートは正である前提（mainで検証済み）
    *amount_usd  = amount_yen / rate_yen_per_usd;
    *amount_euro = amount_yen / rate_yen_per_euro;

    return;
}
