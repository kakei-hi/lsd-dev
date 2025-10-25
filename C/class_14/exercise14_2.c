//
//  サイコロの目を数える
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int     i, num[6];

    // 乱数のシード（種）を設定
    srand((unsigned)time(NULL));

    // カウンターとなる配列の初期化
    for ( i = 0; i < 6; i++)
    {
        num[i] = 0;
    }

    while (num[0] < 10000)
    {
        num[rand() % 6] ++;
    }
    
    for ( i = 0; i < 6; i++)
    {
        printf("\n%dの目が出た回数は%d回です", i + 1, num[i]);
    }
    
    printf("\n");

    return 0;
    

}