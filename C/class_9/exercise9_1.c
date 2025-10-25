//  サイコロの出目

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int     i, dice[6];    //dice[x]: (x +1) の目の出た回数のカウンター

    // rand()のseedを初期化
    srand(((unsigned)time(NULL)));

    // すべての目のカウンターを初期化
    for ( i = 0; i < 6; i++)
    {
        dice[i] = 0;
    }
    
    while (dice[0] < 10000)
    {
        switch (rand() % 6)
        {
            case 0:
                dice[0] ++;
                break;
            case 1:
                dice[1] ++;
                break;
            case 2:
                dice[2] ++;
                break;
            case 3:
                dice[3] ++;
                break;
            case 4:
                dice[4] ++;
                break;
            case 5:
                dice[5] ++;
                break;        
            default:
                break;
        }
    }

    printf("\n");
    for ( i = 0; i < 6; i++)
    {
        printf("%dの目の出た回数は%d回です\n", i + 1, dice[i]);
    }
    
    return 0;

}