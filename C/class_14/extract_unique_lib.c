// extract_unique_lib.c - sample_unique_range の実装（本体とテストで共有）
// ユーザー定義ヘッダは使わず、関数は extern 宣言で参照。

#include <stdlib.h>  // malloc, free, rand

// m..n から p 個を重複なく抽出して out[0..p-1] に格納
// 成功: 0 / 失敗(引数不正やメモリ不足): -1
int sample_unique_range(int m, int n, int p, int* out) {
    if (out == NULL) return -1;
    if (m > n) return -1;
    if (m < 1) return -1;  // 正整数列の前提

    long len_long = (long)n - (long)m + 1L;
    if (len_long < 0 || len_long > 10000000L) {
        return -1;  // 異常または過大（教育用の安全弁）
    }
    int len = (int)len_long;

    if (p < 0 || p > len) return -1;

    int* arr = (int*)malloc((size_t)len * sizeof(int));
    if (arr == NULL) return -1;
    for (int i = 0; i < len; ++i) {
        arr[i] = m + i;
    }

    for (int i = 0; i < p; ++i) {
        int r = i + (rand() % (len - i));  // i..len-1
        int tmp = arr[i];
        arr[i] = arr[r];
        arr[r] = tmp;
        out[i] = arr[i];
    }

    free(arr);
    return 0;
}
