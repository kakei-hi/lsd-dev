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
    // バッファオーバーフロー対策として有効である理由
    // fgetsはバッファサイズ分しか読み込まないため、バッファオーバーフローを防止できます。
    // バッファサイズを超える入力は自動的に切り捨てられるため、安全に文字列を扱えます。
    if (fgets(input_moji, sizeof(input_moji), stdin) == NULL) {
        printf("入力エラー\n");
        return 1;
    }

    // 改行文字が含まれていれば除去
    // fgets関数は、入力時にEnterキーを押すと改行文字('\n')もバッファに格納します。
    // そのため、文字列の末尾が改行文字の場合は、ヌル文字('\0')で上書きして除去します。
    // これにより、文字数カウントや後続の文字列処理が正しく行えます。
    size_t len = strlen(input_moji);
    if (len > 0 && input_moji[len - 1] == '\n') {
        input_moji[len - 1] = '\0';
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
