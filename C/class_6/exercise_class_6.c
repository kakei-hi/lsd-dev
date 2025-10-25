/***********************
 *  九九一覧表
 * ********************/

#include <stdio.h>

int main()
{
    int     i, j;

    // 列のインデックスを表示
    printf("\t");   // タブを挿入
    for ( i = 1; i <= 9; i++)
    {
        printf("%2d\t", i); // %2d: 2桁分のスペースを確保して整数を表示
    }

    printf("\n\n");
    for ( i = 1; i <= 9; i++)
    {
        printf("%2d", i);    // 行のインデックスを表示
        for (j = 1; j <= i; j ++ )
        {
            printf("\t%2d", i * j);
        }
        printf("\n");
    }
    
    return 0;
    
}