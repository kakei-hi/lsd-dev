//
//  main.c
//  exercise
//

#include <stdio.h>

int main() {
    int a, b, c;
    
    //  任意の数値で確かめる
    printf("任意の整数を入力してください\t");
    fscanf(stdin, "%d", &c);
    
    //  b = a++の場合
    a = c;
    b = a++;
    printf("b = a++の場合\n");
    printf("a = %d, b = %d\n\n", a, b);
    
    //  b = ++aの場合
    a = c;
    b = ++a;
    printf("b = ++aの場合\n");
    printf("a = %d, b = %d\n\n", a, b);

    return 0;
}
