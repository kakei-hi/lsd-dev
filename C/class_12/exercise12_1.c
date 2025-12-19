// exercise12_1.c - 配列名と要素アドレス、型依存のアドレス差の確認
// 目的:
//  1. 配列名はその配列の先頭要素のアドレスを示すことを確認
//  2. i番目の要素のアドレスは &a[i-1] または a + (i-1) で表せることを確認
//  3. i番目と(i+1)番目の要素のアドレス差が配列の型（sizeof(T)）に依存することを確認
// 初心者向けに、int/double/char で同じ検証を行い、結果を表示します。

#include <stdio.h>
#include <stdint.h>  // uintptr_t を使ってバイト差を計算
#include <stddef.h>  // ptrdiff_t を使って要素差を計算

// Magic Number回避のため定数化
#define ARRAY_LENGTH 5
#define TEST_INDEX 3  // 「i番目」を 3 として検証（1始まり）

// int型配列での検証
void demonstrate_int(void) {
    int a[ARRAY_LENGTH] = {10, 20, 30, 40, 50};

    // 1) 配列名は先頭要素のアドレス
    int *p_from_name = a;      // 配列名は式中で先頭要素へのポインタに「崩壊」します
    int *p_from_first = &a[0]; // 明示的に先頭要素のアドレス
    printf("[int] 1) a と &a[0] のアドレス\n");
    printf("    a       = %p\n", (void *)p_from_name);
    printf("    &a[0]   = %p\n", (void *)p_from_first);
    printf("    等しい?  %s\n\n", (p_from_name == p_from_first) ? "YES" : "NO");

    // 2) i番目の要素のアドレスの2通りの表現
    int *addr_i_by_amp = &a[TEST_INDEX - 1];
    int *addr_i_by_add = a + (TEST_INDEX - 1);
    printf("[int] 2) %d番目要素のアドレスの2通りの表現\n", TEST_INDEX);
    printf("    &a[%d]   = %p\n", TEST_INDEX - 1, (void *)addr_i_by_amp);
    printf("    a + (%d) = %p\n", TEST_INDEX - 1, (void *)addr_i_by_add);
    printf("    等しい?  %s\n\n", (addr_i_by_amp == addr_i_by_add) ? "YES" : "NO");

    // 3) i番目と(i+1)番目のアドレス差（型に依存）
    int *addr_i = &a[TEST_INDEX - 1];
    int *addr_next = &a[TEST_INDEX];
    ptrdiff_t diff_elements = addr_next - addr_i; // 要素数としての差（常に1）
    uintptr_t diff_bytes = (uintptr_t)(void *)addr_next - (uintptr_t)(void *)addr_i; // バイト差
    printf("[int] 3) %d番目と%d番目のアドレス差\n", TEST_INDEX, TEST_INDEX + 1);
    printf("    要素差        = %td\n", diff_elements);
    printf("    バイト差      = %lu\n", (unsigned long)diff_bytes);
    printf("    sizeof(int)   = %zu\n\n", sizeof(int));
}

// double型配列での検証
void demonstrate_double(void) {
    double a[ARRAY_LENGTH] = {1.1, 2.2, 3.3, 4.4, 5.5};

    double *p_from_name = a;
    double *p_from_first = &a[0];
    printf("[double] 1) a と &a[0] のアドレス\n");
    printf("    a       = %p\n", (void *)p_from_name);
    printf("    &a[0]   = %p\n", (void *)p_from_first);
    printf("    等しい?  %s\n\n", (p_from_name == p_from_first) ? "YES" : "NO");

    double *addr_i_by_amp = &a[TEST_INDEX - 1];
    double *addr_i_by_add = a + (TEST_INDEX - 1);
    printf("[double] 2) %d番目要素のアドレスの2通りの表現\n", TEST_INDEX);
    printf("    &a[%d]   = %p\n", TEST_INDEX - 1, (void *)addr_i_by_amp);
    printf("    a + (%d) = %p\n", TEST_INDEX - 1, (void *)addr_i_by_add);
    printf("    等しい?  %s\n\n", (addr_i_by_amp == addr_i_by_add) ? "YES" : "NO");

    double *addr_i = &a[TEST_INDEX - 1];
    double *addr_next = &a[TEST_INDEX];
    ptrdiff_t diff_elements = addr_next - addr_i;
    uintptr_t diff_bytes = (uintptr_t)(void *)addr_next - (uintptr_t)(void *)addr_i;
    printf("[double] 3) %d番目と%d番目のアドレス差\n", TEST_INDEX, TEST_INDEX + 1);
    printf("    要素差        = %td\n", diff_elements);
    printf("    バイト差      = %lu\n", (unsigned long)diff_bytes);
    printf("    sizeof(double)= %zu\n\n", sizeof(double));
}

// char型配列での検証
void demonstrate_char(void) {
    char a[ARRAY_LENGTH] = {'A', 'B', 'C', 'D', 'E'};

    char *p_from_name = a;
    char *p_from_first = &a[0];
    printf("[char] 1) a と &a[0] のアドレス\n");
    printf("    a       = %p\n", (void *)p_from_name);
    printf("    &a[0]   = %p\n", (void *)p_from_first);
    printf("    等しい?  %s\n\n", (p_from_name == p_from_first) ? "YES" : "NO");

    char *addr_i_by_amp = &a[TEST_INDEX - 1];
    char *addr_i_by_add = a + (TEST_INDEX - 1);
    printf("[char] 2) %d番目要素のアドレスの2通りの表現\n", TEST_INDEX);
    printf("    &a[%d]   = %p\n", TEST_INDEX - 1, (void *)addr_i_by_amp);
    printf("    a + (%d) = %p\n", TEST_INDEX - 1, (void *)addr_i_by_add);
    printf("    等しい?  %s\n\n", (addr_i_by_amp == addr_i_by_add) ? "YES" : "NO");

    char *addr_i = &a[TEST_INDEX - 1];
    char *addr_next = &a[TEST_INDEX];
    ptrdiff_t diff_elements = addr_next - addr_i;
    uintptr_t diff_bytes = (uintptr_t)(void *)addr_next - (uintptr_t)(void *)addr_i;
    printf("[char] 3) %d番目と%d番目のアドレス差\n", TEST_INDEX, TEST_INDEX + 1);
    printf("    要素差        = %td\n", diff_elements);
    printf("    バイト差      = %lu\n", (unsigned long)diff_bytes);
    printf("    sizeof(char)  = %zu\n\n", sizeof(char));
}

int main(void) {
    // 実行開始メッセージ
    printf("=== 配列とポインタの確認 (exercise12_1) ===\n\n");

    // 型ごとに検証を実施
    demonstrate_int();
    demonstrate_double();
    demonstrate_char();

    return 0;
}
