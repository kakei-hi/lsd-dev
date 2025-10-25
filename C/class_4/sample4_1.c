// サンプルコード4_1

#include <stdio.h>

int main(){
    int     a = 1, b = 2, c = 3;

    printf("\n(a, b, c) = (%d, %d, %d)のとき\n", a, b, c);

    // a == b
    printf("\na == bは");
    if(a ==b){
        printf("TRUE");
    }
    else {
        printf("FALSE");
    }
    printf("です\n");

    // a < b && (a + b) == c
    printf("\na < b && (a + b) == cは");
    if(a < b && (a + b) == c){
        printf("TRUE");
    }
    else {
        printf("FALSE");
    }
    printf("です\n");

    // a > b || c != (a + b)
    printf("\na > b || c != (a + b)は");
    if(a > b || c != (a + b)){
        printf("TRUE");
    }
    else {
        printf("FALSE");
    }
    printf("です\n");

   // ! a < 0
    printf("\n! a < 0は");
    if(! a < 0){
        printf("TRUE");
    }
    else {
        printf("FALSE");
    }
    printf("です\n");

    return 0;

}