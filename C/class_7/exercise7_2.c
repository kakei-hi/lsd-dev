//  数を数える

#include <stdio.h>

int main()
{
    int     i, m, n, p;
    int     count;

    printf("\nm, n, pの値を入力してください ex. 3,124,7\t");
    fscanf(stdin, "%d, %d, %d", &m, &n, &p);

    count = 0;              // カウンターを初期化する
    for ( i = m ; i <= n; i++)
    {
        if ((i % p) == 0)   // pで割り切れたらiはpの倍数
        {
            count ++;
        }
        
    }

    printf("\n%dから%dの間には%dの約数が%d個あります\n", m, n, p, count);

    return 0;

}