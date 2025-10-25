// サイコロを振る

#include    <stdio.h>       // 最初にインクルードする
#include    <stdlib.h>      // rand(), srand()の使用に必要
#include    <time.h>        // time()の使用に必要

int main()
{
    int     i, num, count;

    //  rand()のseedを決定する
    srand((unsigned)time(NULL));

    // カウンターの初期化
    count = 0;
    for ( i = 0; i < 10000; i++)
    {
        // 1以上6以下の乱数を発生する
        num = (rand() % 6) + 1;
        if (num == 1){
            count ++;
        }
    }

    printf("\n1の目が出た回数は%d回です\n", count);

    return 0;
    
}