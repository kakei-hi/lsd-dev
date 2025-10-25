//
//  ダブルポインタ
//

#include    <stdio.h>

int main()
{
    int		val = 123;
    int		*ptr1, **ptr2;
    
    ptr1 = &(val);
    ptr2 = &(ptr1);

    printf("val = %d, *ptr1 = %d, **ptr2 = %d\n", val, *ptr1, **ptr2);

    //valのアドレスとptr1の値
    printf("&val = %p, ptr1 = %p \n", &val, ptr1);

    // ptr1のアドレスとptr2の値
    printf("&ptr1 = %p, ptr2 = %p \n", &ptr1, ptr2);

    return 0;

}