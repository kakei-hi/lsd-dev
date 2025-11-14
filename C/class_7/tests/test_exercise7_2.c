// exercise7_2.c のテストコード
// 倍数カウント機能の動作確認

#include <stdio.h>
#include <stdlib.h>

/**
 * 指定範囲内のpの倍数を数える関数（テスト用に分離）
 * @param m 範囲の開始値
 * @param n 範囲の終了値
 * @param p 倍数の基準となる数
 * @return pの倍数の個数
 */
int count_multiples(int m, int n, int p)
{
    int i;
    int multiple_count = 0;

    // pが0の場合はエラー
    if (p == 0)
    {
        return -1;
    }

    // mがnより大きい場合はエラー
    if (m > n)
    {
        return -1;
    }

    // mからnまでの範囲でpの倍数を数える
    for (i = m; i <= n; i++)
    {
        if ((i % p) == 0)
        {
            multiple_count++;
        }
    }

    return multiple_count;
}

/**
 * テスト実行用の関数
 */
void run_tests()
{
    int result;

    printf("=== exercise7_2 のテスト開始 ===\n\n");

    // テスト1: 基本的な動作確認
    printf("テスト1: 3から124の間の7の倍数\n");
    result = count_multiples(3, 124, 7);
    printf("結果: %d個 (期待値: 17個)\n", result);
    printf("%s\n\n", (result == 17) ? "✓ 成功" : "✗ 失敗");

    // テスト2: 境界値テスト（開始値が倍数）
    printf("テスト2: 10から20の間の5の倍数\n");
    result = count_multiples(10, 20, 5);
    printf("結果: %d個 (期待値: 3個)\n", result);
    printf("%s\n\n", (result == 3) ? "✓ 成功" : "✗ 失敗");

    // テスト3: 範囲内に倍数がない場合
    printf("テスト3: 1から5の間の10の倍数\n");
    result = count_multiples(1, 5, 10);
    printf("結果: %d個 (期待値: 0個)\n", result);
    printf("%s\n\n", (result == 0) ? "✓ 成功" : "✗ 失敗");

    // テスト4: 異常系テスト（pが0）
    printf("テスト4: pが0の場合のエラー処理\n");
    result = count_multiples(1, 10, 0);
    printf("結果: %d (期待値: -1)\n", result);
    printf("%s\n\n", (result == -1) ? "✓ 成功" : "✗ 失敗");

    // テスト5: 異常系テスト（m > n）
    printf("テスト5: m > nの場合のエラー処理\n");
    result = count_multiples(10, 5, 3);
    printf("結果: %d (期待値: -1)\n", result);
    printf("%s\n\n", (result == -1) ? "✓ 成功" : "✗ 失敗");

    printf("=== テスト終了 ===\n");
}

int main()
{
    run_tests();
    return EXIT_SUCCESS;
}
