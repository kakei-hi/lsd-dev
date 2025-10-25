/*
 *  複合した条件式
 *  最大の変数を求める
 *
 */

#include <stdio.h>

int main()
{
    int     a1, a2, a3;     //  整数型
    
    printf("\n整数を3つ入力して下さい (ex. 3,20,18)\t");
    fscanf(stdin, "%d, %d, %d", &a1, &a2, &a3);
    //  複数の変数も1つのfscanfで入力可
    //  変数の前には'&'を付す
    
    printf("a1 = %d, a2 = %d, a3 = %d", a1, a2, a3);
    
    printf("\n最大値は");
    if (a1 >= a2 && a1 >= a3) {
        printf("a1");
    }
    else if (a2 >= a3){
        printf("a2");
    }
    else{
        printf("a3");
    }    
    printf("です\n");
    
    return 0;
    
}
