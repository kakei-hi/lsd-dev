//
//  日数のカウント
//

#include <stdio.h>

int main()
{
    int     i, nn, mm;

    printf("\n今日からN日後までを考えます\t");
    fscanf(stdin, "%d", &nn);

    // 条件を満たす日数を数えるカウンター
    mm = 0;
    for ( i = 0; i <= nn; i++)
    {
        // 日曜日: (i % 7) == 4     仏滅ではない: (i % 6) != 3 
        if (((i % 7 ) == 4) && ((i % 6) != 3))
        {
            mm ++;
        }
    }
    printf("\n今日から%d日後までに仏滅ではない日曜日は%d日あります", nn, mm);

    printf("\n");

    return 0;
    
}