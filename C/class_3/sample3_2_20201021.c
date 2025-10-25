#include    <stdio.h>

int main()
{
    // 変数の宣言
    int     num1, num2;
    float   num3;
    char    x, y;

    printf("\nnum1 = %d", num1);

    printf("\n変数に値を代入");
    num1 = 2;
    printf("\nnum1 = %d, num2 = %d", num1, num2);
    num2 = 5;
    num1 = num2;
    num2 = num1 + num2;
    printf("\nnum1 = %d, num2 = %d", num1, num2);

    num3 = 2.71828;
    printf("\nnum3 = %d", num3);
    // 変数仕様と変数の型がマッチしていないので正しい値は表示されない

    x = 121;
    y = x;       // シングルクォーテーションなし
    printf("\ny = %d\ty = %c", y, y);

    y = 'x';    // シングルクォーテーションあり
    printf("\ny = %d\ty = %c \n", y, y);

}