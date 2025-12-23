//
//  2次元配列の自動確保
//

#include    <stdio.h>
#include    <stdlib.h>
#include    <limits.h>   // SIZE_MAX を使用するため追加

// 2次元配列サイズ（Magic Numberの定数化）
#define ROW_COUNT 3
#define COL_COUNT 4

int main()
{
    // 行ポインタ配列と連続データ領域に分けて確保する方式
    float   **row_ptrs = NULL;
    float   *data_buffer = NULL;
    const size_t  row_count = ROW_COUNT;
    const size_t  col_count = COL_COUNT;
    size_t  row, col;

    // メモリ確保（Cではmallocのキャスト不要、sizeofは対象の実体で書く）
    row_ptrs = malloc(row_count * sizeof(*row_ptrs));

    // 要素数計算のオーバーフローを事前に検出
    if (col_count != 0 && row_count > SIZE_MAX / col_count) {
        printf("サイズ計算がオーバーフローします\n");
        free(row_ptrs);
        exit(EXIT_FAILURE);
    }

    const size_t total_elems = row_count * col_count;
    data_buffer = malloc(total_elems * sizeof(*data_buffer));

    // 両方の確保結果を検証。失敗時は後始末して終了
    if (row_ptrs == NULL || data_buffer == NULL) {
        printf("メモリの確保に失敗しました\n");
        free(row_ptrs);
        free(data_buffer);
        exit(EXIT_FAILURE);
    }

    // 行ごとの先頭アドレスを設定（行は連続領域を等分に指す）
    for (row = 0; row < row_count; row++) {
        row_ptrs[row] = data_buffer + row * col_count;
    }

    // 各要素に値を代入する
    for (row = 0; row < row_count; row++) {
        for (col = 0; col < col_count; col++) {
            row_ptrs[row][col] = 10.0f * row + col;
        }
    }

    // 出力
    for (row = 0; row < row_count; row++) {
        for (col = 0; col < col_count; col++) {
            printf("array[%zu][%zu] = %f \n", row, col, row_ptrs[row][col]);
        }
        printf("\n");
    }

    // 後始末
    free(row_ptrs);
    free(data_buffer);

    return 0;
}
