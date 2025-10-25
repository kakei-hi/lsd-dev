#include <stdio.h>

int main()
{
    char    ch;     // chという変数名のchar型の変数を宣言
    int     a, b;   // aおよびbという変数名のint型の変数を宣言
    float   p;      // pという変数名のfloat型の変数を宣言

    printf("\nアルファベットを1文字入力してEnterを押して下さい\t");
    // Windowsでは\（バックスラッシュ）は半角の¥

    fscanf(stdin, "%c", &ch);
    // fscanf(): 必ず変数の前に&を付ける

    printf("入力されたアルファベットは%cです", ch);

    a = 10;
    printf("\na = %d, b = %d", a, b);

    p = 3.14159;
    printf("\n円周率の値は%fです", p);

    printf("\nアルファベットを1文字入力してEnterを押して下さい\t");
    fscanf(stdin, "%c", &ch);   //この1文がなければどうなるかを試してみる
    fscanf(stdin, "%c", &ch);
    printf("入力されたアルファベットは%cです\n", ch);

    return 0;
    
}
