#include <stdio.h>

int main()
{
    int     x = 1, y = 2;
    int     *ip;    // ip: ポインタ 変数のアドレスを格納する
                    // ポインタ名: ip
                    // ポインタを宣言する時は"*（ポインタ名）"と宣言する
    
    printf("\nx = %d", x);
    printf("\ny = %d", y);

    ip = &x;

    printf("\n\n&x = %p", &x);  // アドレスを扱う時の変数仕様は"%p"
    printf("\n&y = %p", &y);

    y = *ip;

    *ip = 0;
    printf("\n");
    printf("\nx = %d", x);
    printf("\ny = %d", y);

    printf("\n");

    return 0;

}