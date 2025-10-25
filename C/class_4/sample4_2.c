// サンプルコード4_2

#include <stdio.h>

int main(){
    int     year;

    printf("\n任意の正整数を入力してください\t");
    fscanf(stdin, "%d", &year);

    if ((year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0))){
        printf("閏年");
    }
    else{
        printf("平年");
    }
    printf("です\n");

    return 0;

}