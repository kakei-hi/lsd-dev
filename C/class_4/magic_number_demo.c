/*
 * magic_number_demo.c
 * Magic Number（マジックナンバー）について学ぶためのサンプル
 * 購入価格計算
 */

#include <stdio.h>

/* 定数で意味を与える例 */
#define CONSUMPTION_TAX_RATE 0.1 /* 例: 10% の消費税 */
#define DISCOUNT_RATE 0.1
#define SHIPPING_FEE 500.0

int main(void) {

    float price = 500; /* 税抜価格 */

    /* マジックナンバーを直接書く場合 (0.1 を直書き) */
    float payment_amount = price * (1 - 0.1 )* (1 + 0.1) + 500; /* 0.1 が何を意味するか判断しづらい */

    printf("=== 支払い金額 ===\n");
    printf("税抜価格 = %.1f 円\n", price);
    printf("消費税 = %.1f\n", price * 0.1);
    printf("割引額 = %.1f\n", price * 0.1);
    printf("送料 = %.1f\n", 500.0);
    printf("支払い価格 = %f\n", payment_amount);

    return 0;
}
