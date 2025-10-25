/*******************************
 *  整数の総和を求める
 * ****************************/

#include <stdio.h>

int main()
{
    int     i, m, n, sum;

    printf("\nmからnまでの和を求めます．");
    printf("\nm, nの値を入力してください．ただし，m <= nとする．(ex. 3,10)\t");
    fscanf(stdin, "%d, %d", &m, &n);

    sum = 0;    // 総和を代入する変数を初期化する

    // forのインデックスiを足すべき数とする
    for (i = m; i <= n; i++){
        sum += i;   // sumにiを足した数をsumに代入する
    }
    
    printf("\n%dから%dまでの和は%dです\n", m, n, sum);

    return 0;

}
