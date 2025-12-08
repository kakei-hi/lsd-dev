/************************
    入力された文字数を取得
************************/

#include <stdio.h>
#include <string.h>

// 配列の最大サイズを定数化
#define MAX_INPUT_SIZE 100

int main()
{
    int n;
    char input_moji[MAX_INPUT_SIZE];      // 99文字（英数半角）を入力できる配列

    printf("\n文字列を入力して下さい\t");
    if (scanf("%s", input_moji) != 1) {
        printf("入力エラー\n");
        return 1;
    }

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
