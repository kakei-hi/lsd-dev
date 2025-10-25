#include    <stdio.h>

int main(){
    int		a;
    float	b;
    
    // Q-1
    b = 3.5; a = b;
    printf("a = %d", a);

    // Q-2
    a = 5; b = a;
    printf("b = %f", b);

    // Q-3
    b = 5 / 3;
    printf("b = %f", b);

    // Q-4
    b = 5 / 3.0;
    printf("b = %f", b);

    // Q-5
    a = 5.0 / 3.0;
    printf("a = %d", a);

    // Q-6
    b = (float)5 / (float)3.0;
    printf("b = %f", b);

    // Q-7
    b = (float)(5 / 3);
    printf("b = %f", b);

    // Q-8
    a = 3;
    b = 5 / (float)a;
    printf("b = %f", b);

    return 0;
    
}