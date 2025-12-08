//
//  配列名とアドレス
//

#include <stdio.h>

int main()
{
    int     a[5], i;
    char    b[5] = {'A', 'B', 'C', 'D', 'E'};

    for ( i = 0; i < 5; i++)
    {
        a[i] = i;
    }


    printf("\nアドレス");
    for ( i = 0; i < 5; i++)
    {
        printf("\n&a[%d] = %p, a = %p", i, &a[i], (a + i));
    }   
    printf("\n格納されている値");
    for ( i = 0; i < 5; i++)
    {
        printf("\n*(&a[%d]) = %d, *(a + %d) = %d", i, *(&a[i]), i, *(a + i));
    }

    printf("\nアドレス");
    for ( i = 0; i < 5; i++)
    {
        printf("\n&b[%d] = %p, b = %p", i, &b[i], (b + i));
    }    
    printf("\n格納されている値");
    for ( i = 0; i < 5; i++)
    {
        printf("\n*(&b[%d]) = %c, *(b + %d) = %c", i, *(&b[i]), i, *(b + i));
    }

    printf("\n");

    return 0;

}