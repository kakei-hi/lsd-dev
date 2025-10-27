// サンプルコード4_1

#include <stdio.h>
#include <stdbool.h>

/* 表示用の定数化（Magic Number や文字列の統一） */
#define TRUE_TEXT  "TRUE"
#define FALSE_TEXT "FALSE"

int main(void){
    int     value_a = 1, value_b = 2, value_c = 3;

    printf("\n(a, b, c) = (%d, %d, %d)のとき\n", value_a, value_b, value_c);

    /* a == b を評価 */
    bool is_equal = (value_a == value_b);
    printf("\na == bは");
    if (is_equal) {
        printf("%s", TRUE_TEXT);
    } else {
        printf("%s", FALSE_TEXT);
    }
    printf("です\n");

    /* a < b && (a + b) == c を評価 */
    bool is_and_sum_equal = (value_a < value_b) && ((value_a + value_b) == value_c);
    printf("\na < b && (a + b) == cは");
    if (is_and_sum_equal) {
        printf("%s", TRUE_TEXT);
    } else {
        printf("%s", FALSE_TEXT);
    }
    printf("です\n");

    /* a > b || c != (a + b) を評価 */
    bool is_or_sum_not_equal = (value_a > value_b) || (value_c != (value_a + value_b));
    printf("\na > b || c != (a + b)は");
    if (is_or_sum_not_equal) {
        printf("%s", TRUE_TEXT);
    } else {
        printf("%s", FALSE_TEXT);
    }
    printf("です\n");

    /* "! a < 0" の意図を明確化して評価
       元の書き方は誤解を招くので、ここでは「a は 0 未満ではない（a >= 0）」という意図で実装 */
    bool is_not_less_than_zero = !(value_a < 0);
    printf("\n! a < 0は");
    if (is_not_less_than_zero) {
        printf("%s", TRUE_TEXT);
    } else {
        printf("%s", FALSE_TEXT);
    }
    printf("です\n");

    return 0;

}
