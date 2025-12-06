/************************
     文字列の追加 / 比較
**************************/

#include <stdio.h>
#include <string.h>

// 配列の最大サイズを定数化
#define MAX_INPUT_SIZE 100

// 入力バッファをクリアして二重入力を防止する
void clear_input_buffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        // ...existing code...
    }
}

int main()
{
    int     i, n;
    char    input_moji[MAX_INPUT_SIZE], copy_moji[MAX_INPUT_SIZE];      // 99文字（英数半角）を入力できる配列

    printf("\n文字列を入力して下さい\t");
    if (scanf("%s", input_moji) != 1) {
        printf("入力エラー\n");
        return 1;
    }
    clear_input_buffer(); // 二重入力回避

    strcpy(copy_moji, input_moji);          //  文字列のコピー
    printf("\n文字列1: %s, 文字列2: %s", input_moji, copy_moji);
    if (strcmp(input_moji, copy_moji) == 0) // 文字列の比較
    {
        printf("\n文字列は一致しています．");
    }
    else
    {
        printf("\n文字列は一致していません．");
    }
    printf("\n");

    strcat(copy_moji, input_moji);          //  文字列の連結
    printf("\n文字列1: %s, 文字列2: %s", input_moji, copy_moji);
    if (strcmp(input_moji, copy_moji) == 0)
    {
        printf("\n文字列は一致しています．");
    }
    else
    {
        printf("\n文字列は一致していません．");
    }
    printf("\n");

    return 0;

}
