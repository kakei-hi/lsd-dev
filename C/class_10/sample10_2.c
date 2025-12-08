/************************
     先頭からn文字を出力する
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
    char    input_moji[MAX_INPUT_SIZE];      // 99文字（英数半角）を入力できる配列

    printf("\n文字列を入力して下さい\t");
    if (scanf("%s", input_moji) != 1) {
        printf("入力エラー\n");
        return 1;
    }

    printf("\n出力する文字数を入力して下さい\t");
    if (scanf("%d", &n) != 1) {
        printf("入力エラー\n");
        return 1;
    }
    clear_input_buffer(); // 二重入力回避

    printf("\n入力された文字列の冒頭%d文字は", n);
    for ( i = 0; i < n; i++)
    {
        printf("%c", input_moji[i]);
    }
    printf("です\n");
    
    return 0;

}
