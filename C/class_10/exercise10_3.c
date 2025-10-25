/************************
     文字列の追加 / 比較
**************************/

#include <stdio.h>
#include <string.h>

int main()
{
    int     i, n;
    char    input_moji[100], copy_moji[100];      // 99文字（英数半角）を入力できる配列

    printf("\n文字列を入力して下さい\t");
    fscanf(stdin, "%s", input_moji);

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