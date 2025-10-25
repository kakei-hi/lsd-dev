//
//  2次元配列の自動確保
//

#include    <stdio.h>
#include    <stdlib.h>

int main()
{
    float   **array1, *array2;  // array1: 値が格納された場所を指し示すポインタ(array1)を
                                // 指し示すポインタ
    int     m = 3, n = 4;
    int     i, j;

    array1 = (float **)malloc(m * sizeof(float *));
    array2 = (float *)malloc(m * n * sizeof(float));

    for ( i = 0; i < m; i ++){
        array1[i] = array2 + i * n;
    }

    // メモリの確保に失敗した場合は終了する
    if ( array2 == NULL){
        printf("メモリの確保に失敗しました\n");
        exit(1);
    }

    // 各要素に値を代入する
    for ( i = 0; i < m; i ++ ){
        for ( j = 0; j < n; j ++ ){
            array1[i][j] = 10.0 * i + j;
        }
    }

    for ( i = 0; i < m; i ++){
        for ( j = 0; j < n; j ++){
            printf("array[%d][%d] = %f \n", i, j, array1[i][j]);
        }
        printf("\n");
    }
   
    free(array1);
    free(array2);

    return 0;

}