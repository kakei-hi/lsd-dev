// サイコロを振る

#include    <stdio.h>       // 最初にインクルードする
#include    <stdlib.h>      // rand(), srand()の使用に必要
#include    <time.h>        // time()の使用に必要

int main()
{
    int     num, freq_1, count_dice;

    //  rand()のseedを決定する
    srand((unsigned)time(NULL));

    // カウンターの初期化
    // freq_1: 1の目の出た回数
    // count_dice: サイコロを振った回数
    freq_1 = count_dice = 0;

    while(freq_1 < 10000)
    {
        num = (rand() % 6) + 1;
        if (num == 1){
            freq_1 ++;
        }
        count_dice ++;     
    }

    printf("\nサイコロを振った回数は%d回です\n", count_dice);

    return 0;
    
}