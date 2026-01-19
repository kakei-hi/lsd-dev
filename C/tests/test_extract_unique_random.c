// tests/test_extract_unique_random.c - 教育用テスト（標準出力で結果確認）
// main関数とは別にテスト用関数を作成、境界値や異常系を含める方針。
// ユーザー定義ヘッダは使わず、必要な宣言は extern で記載。

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

extern int sample_unique_range(int m, int n, int p, int* out);

static int has_duplicate(const int* a, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (a[i] == a[j]) return 1;
        }
    }
    return 0;
}

static int in_range_all(const int* a, int n, int lo, int hi) {
    for (int i = 0; i < n; ++i) {
        if (a[i] < lo || a[i] > hi) return 0;
    }
    return 1;
}

static void test_case(const char* name, int m, int n, int p, unsigned seed) {
    int len = (n - m + 1);
    int* out = p > 0 ? (int*)malloc((size_t)p * sizeof(int)) : NULL;

    srand(seed);  // 決定的にする
    int rc = sample_unique_range(m, n, p, out);

    if (m > n || m < 1 || p < 0 || p > len) {
        printf("[%-20s] EXPECT FAIL -> rc=%d : %s\n", name, rc, (rc != 0 ? "PASS" : "FAIL"));
        if (out) free(out);
        return;
    }

    if (rc != 0) {
        printf("[%-20s] UNEXPECTED FAIL rc=%d\n", name, rc);
        if (out) free(out);
        return;
    }

    if (p == 0) {
        printf("[%-20s] PASS (p=0)\n", name);
        if (out) free(out);
        return;
    }

    int ok = 1;
    if (!in_range_all(out, p, m, n)) ok = 0;
    if (has_duplicate(out, p)) ok = 0;

    printf("[%-20s] %s\n", name, ok ? "PASS" : "FAIL");
    if (!ok) {
        printf("  -> m=%d n=%d p=%d : ", m, n, p);
        for (int i = 0; i < p; ++i) printf("%d%s", out[i], (i+1<p)?" ":"\n");
    }

    free(out);
}

int main(void) {
    // 正常系
    test_case("typical",        3, 10, 4, 1234U);
    test_case("full-pick",      1, 5,  5, 5678U);
    test_case("p-zero",         2, 7,  0, 42U);

    // 境界系
    test_case("single-elem",    5, 5,  1, 1U);

    // 異常系（fail 期待）
    test_case("m>n",            7, 3,  2, 99U);
    test_case("m<1",           -1, 3,  2, 99U);
    test_case("p<0",            1, 3, -1, 99U);
    test_case("p>len",          1, 3,  5, 99U);

    return 0;
}
