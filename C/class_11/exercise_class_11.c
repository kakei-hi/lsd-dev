/*
 *
 *	関数にアドレスを引き渡す
 *	変数を入れ替える
 *
 */


#include <stdio.h>

// swap関数のプロトタイプ宣言をファイルの先頭に移動
void swap(int *a, int *b);

int main(void) // 引数がないことをvoidで明示
{
    int num1, num2;

    printf("\n整数を2つ入力してください\t\t");
    fscanf(stdin, "%d,%d", &num1, &num2);
    
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
