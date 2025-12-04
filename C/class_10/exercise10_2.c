/************************
     先頭からn文字を出力する
**************************/

#include <stdio.h>
#include <string.h>

// 配列の最大サイズを定数化
#define MAX_INPUT_SIZE 100

// 入力バッファをクリアする関数
void clear_input_buffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main()
{
    int     i, n;
    char    input_moji[MAX_INPUT_SIZE];      // 99文字（英数半角）を入力できる配列

    printf("\n文字列を入力して下さい\t");
    // バッファオーバーフロー回避のため、fgetsを使用
    if (fgets(input_moji, sizeof(input_moji), stdin) == NULL) {
        printf("入力エラー\n");
        return 1;
    }
    // 入力バッファをクリア（二重入力回避）
    clear_input_buffer();

    printf("\n出力する文字数を入力して下さい\t");
    // 数値入力後のバッファクリア処理を追加
    if (scanf("%d", &n) != 1) {
        printf("入力エラー\n");
        return 1;
    }
    // 入力バッファをクリア（二重入力回避）
    clear_input_buffer();
  
    printf("\n入力された文字列の冒頭%d文字は", n);
    for ( i = 0; i < n; i++)
    {
        printf("%c", input_moji[i]);
    }
    printf("です\n");
    
    return 0;

}
