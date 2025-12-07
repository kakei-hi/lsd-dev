/************************
     先頭からn文字を出力する
**************************/

#include <stdio.h>
#include <string.h>

// 配列の最大サイズを定数化
//#define MAX_INPUT_SIZE 100
#define MAX_INPUT_SIZE 2
#define INPUT_BUFFER_SIZE (MAX_INPUT_SIZE + 2)

// 入力バッファをクリアして二重入力を防止する
void clear_input_buffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        // 何もしない（バッファをクリアするためのループ）
    }
}

int main()
{
    int     i, n;
    char    input_moji[INPUT_BUFFER_SIZE];      // 入力上限＋改行＋終端を想定したサイズ

    printf("\n文字列を入力して下さい\t");
    // fgetsで安全に文字列を取得（バッファオーバーフロー防止）
    if (fgets(input_moji, INPUT_BUFFER_SIZE, stdin) == NULL) {
        printf("入力エラー\n");
        return 1;
    }
    // 入力文字数がMAX_INPUT_SIZE以上なら終了（改行欠落で判定）
    char *newline_pos = strchr(input_moji, '\n');
    if (newline_pos == NULL) {
        clear_input_buffer();
        printf("入力が長すぎます。%d文字未満で入力してください。\n", MAX_INPUT_SIZE);
        return 1;
    }
    // fgetsで取得した文字列の末尾の改行を除去
    *newline_pos = '\0';
    size_t len = strlen(input_moji);
    if (len >= MAX_INPUT_SIZE) {
        printf("入力が長すぎます。%d文字未満で入力してください。\n", MAX_INPUT_SIZE);
        return 1;
    }

    printf("\n出力する文字数を入力して下さい\t");
    if (scanf("%d", &n) != 1) {
        printf("入力エラー\n");
        return 1;
    }
    clear_input_buffer(); // 二重入力回避

    printf("\n入力された文字列の冒頭%d文字は", n);
    // 入力文字数と配列長の境界チェック
    for ( i = 0; i < n && i < strlen(input_moji); i++)
    {
        printf("%c", input_moji[i]);
    }
    printf("です\n");
    
    return 0;

}
