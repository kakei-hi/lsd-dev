//
//  メモリ領域の動的確保
//

#include    <stdio.h>
#include    <stdlib.h>  // for malloc(), free() 

int main()
{
    int     n = 5;
    float   *array;

    int     i;

    // メモリ領域を動的に確保
    array = (float *)malloc(n * sizeof(float));

    // 各要素の値とアドレスを表示
    printf("array = %p \n", array);
    for ( i = 0; i  <  n; i++)
    {
        printf("array[%d] = %f &array[%d] = %p \n", i, array[i], i, array + i);
    }

    printf("配列arrayに値を代入\n");
    for ( i = 0; i < n; i++)
    {
       *(array + i) = i * 10.0; // array[i] =  i * 10.0;と同等
       printf("array[%d] = %f \n", i, array[i]);
    }

    // mallocで確保したメモリ領域を開放
    free(array);
    
    return 0;
    
}
