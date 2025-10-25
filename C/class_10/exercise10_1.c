/************************
    入力された文字数を取得
************************/

#include <stdio.h>
#include <string.h>

int main()
{
    int     n;
    char    input_moji[100];      // 99文字（英数半角）を入力できる配列

    printf("\n文字列を入力して下さい\t");
    fscanf(stdin, "%s", input_moji);

    // 文字列操作関数
    n = strlen(input_moji);     // 文字数のカウント
    printf("\n入力された文字数は%d文字です", n);

    // ループ処理
    n = 0;
    while(input_moji[n] != '\0'){
        n ++;
    }
    printf("\n入力された文字数は%d文字です", n);

    printf("\n");

    return 0;

}