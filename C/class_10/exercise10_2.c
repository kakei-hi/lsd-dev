/************************
     先頭からn文字を出力する
**************************/

#include <stdio.h>
#include <string.h>

int main()
{
    int     i, n;
    char    input_moji[100];      // 99文字（英数半角）を入力できる配列

    printf("\n文字列を入力して下さい\t");
    fscanf(stdin, "%s", input_moji);

    printf("\n出力する文字数を入力して下さい\t");
    fscanf(stdin, "%d", &n);    
  
    printf("\n入力された文字列の冒頭%d文字は", n);
    for ( i = 0; i < n; i++)
    {
        printf("%c", input_moji[i]);
    }
    printf("です");
    
    printf("\n");


    return 0;

}