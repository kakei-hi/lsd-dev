#include <stdio.h>

int main(void) {

    float price = 500; /* 税抜価格 */

    /* マジックナンバーを直接書く場合 (0.1, 500 を直書き) */
    float payment_amount = price * (1 - 0.1) * (1 + 0.1) + 500; /* 0.1;
    
    return 0;
}