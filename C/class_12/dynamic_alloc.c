//
//  メモリ領域の動的確保
//

#include    <stdio.h>
#include    <stdlib.h>  // for malloc(), free() 

// マジックナンバーの定数化
#define DEFAULT_COUNT 5
#define STEP_VALUE    10.0f

int main()
{
    size_t  count = DEFAULT_COUNT;     // 要素数
    float   *array = NULL;             // ポインタを初期化しておく

    // メモリ領域を動的に確保（NULLチェックを追加）
    array = malloc(count * sizeof(float));
    if (array == NULL) {
        fprintf(stderr, "メモリ領域の確保に失敗しました。\n");
        return EXIT_FAILURE; // 変更: 数値ではなくマクロを使用
    }

    printf("array = %p \n", (void *)array);

    // 先に初期化してから値を表示（未初期化読み取りの回避）
    printf("配列arrayに値を代入\n");
    for (size_t idx = 0; idx < count; idx++)
    {
        array[idx] = (float)idx * STEP_VALUE; // array[idx] と *(array + idx) は同等
        printf("array[%zu] = %f \n", idx, array[idx]);
    }

    // 各要素の値とアドレスを表示
    printf("各要素のアドレスを表示\n");
    for (size_t idx = 0; idx < count; idx++)
    {
        printf("array[%zu] = %f &array[%zu] = %p \n",
               idx, array[idx], idx, (void *)(array + idx));
    }

    // mallocで確保したメモリ領域を開放
    free(array);
    
    return EXIT_SUCCESS; // 変更: 数値ではなくマクロを使用
    
}
