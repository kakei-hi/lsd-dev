/*
 *
 *	関数にアドレスを引き渡す
 *	変数を入れ替える
 *
 */


#include <stdio.h>

// 入力バッファをクリアする関数（改行まで読み捨てる）
void clear_input_buffer(void) {
    int ch;
    // 改行またはEOFまで読み捨てることで二重入力を防止
    while ((ch = getchar()) != '\n' && ch != EOF) {
        // 何もしない
    }
}

// swap関数のプロトタイプ宣言をファイルの先頭に移動
void swap(int *a, int *b);

int main(void) // 引数がないことをvoidで明示
{
    int num1, num2;

    printf("\n整数を2つ入力してください（例: 12,34）\t\t");
    // scanfに置換し，戻り値で入力成功を確認
    if (scanf("%d,%d", &num1, &num2) != 2) {
        printf("\n入力形式が正しくありません。例: 12,34\n");
        // 誤った入力をバッファから除去
        clear_input_buffer();
        return 1;
    }
    // 入力直後にバッファをクリアして二重入力を回避
    clear_input_buffer();
    
    printf("\nひとつめの数字は%d, ふたつめの数字は%d です", num1, num2);

    printf("\n数字を入れ替えます");
    //	数字を入れ替える
    swap(&num1, &num2);

    printf("\nひとつめの数字は%d, ふたつめの数字は%d です\n\n", num1, num2);

    return 0;
    
}


//
//	数字を入れ替える
//

void swap(int *a, int *b)
{
    int temp;

    temp = *a;
    *a = *b;
    *b = temp;

    // void関数ではreturnは省略可能
}
