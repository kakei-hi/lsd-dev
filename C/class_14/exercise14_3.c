//
//   乱数を利用して円周率を求める
//

#include    <stdio.h>
#include    <stdlib.h>
#include    <time.h>

// 正方形の面積 = 繰り返し回数
#define     square_c    100000

int main()
{
    int     circle_c, i;
    float   point_x, point_y;

    // 乱数のシードを設定
    srand((unsigned)time(NULL));

    //  半径1の4分円内に含まれる点の数
    circle_c = 0;
    for ( i = 0; i < square_c; i++)
    {
        // 0以上1以下の乱数を生成
        point_x = (float)rand() / (float)RAND_MAX;
        point_y = (float)rand() / (float)RAND_MAX;

        // (point_x, point_y)が半径1の四分円内ならば
        if (((point_x * point_x) + (point_y * point_y)) < 1.0)
        {
            circle_c ++;
        }
    }

    // 正方形と内接する4分円の面積比より円周率を計算
    printf("\nPI = %f", 4.0 * (float)circle_c / (float)square_c);

    printf("\n");

    return 0;
    
}