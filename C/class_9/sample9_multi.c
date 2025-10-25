// 多次元配列

#include <stdio.h>

int main() 
{
    int     i, score[2][3] = {{60, 88, 92}, {48, 76, 94}};

    printf("\n");
    for ( i = 0; i < 2; i++)
    {
        printf("%d人目の成績です\n", i + 1);
        printf("数学の点数は%dです\n", score[i][0]);
        printf("物理の点数は%dです\n", score[i][1]);
        printf("英語の点数は%dです\n", score[i][2]);
    }
    

    return 0;
}