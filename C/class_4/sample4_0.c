// keynote用コード
#include    <stdio.h>

int main()
{
    int     a, b;
    float   fa;

    a = 1; b = 2;

    printf("a > bの真偽値は%d\n", a > b);
    printf("a < 2の真偽値は%d\n", a < 2);
    printf("(a + b) != (a + 1)の真偽値は%d\n", (a + b) != (a + 1));
    printf("2 >= (a + 1)の真偽値は%d\n", 2 >= (a + 1));

    if (a == 2){
        printf("aの値は2です\n");
    }
    else {
        printf("aの値は2ではありません\n");
    }

    if (a = 3){
        printf("aの値は2です\n");
    }
    else {
        printf("aの値は2ではありません\n");
    }

    int     a = 1;

    if (a = -1){
        printf("aの値は2です\n");
    }
    else {
        printf("aの値は2ではありません\n");
    }

    if (a = 0){
        printf("aの値は2です\n");
    }
    else {
        printf("aの値は2ではありません\n");
    }

    printf("()a = 3)が返す値は%d\n", (a = 3));

    return 0;
 }