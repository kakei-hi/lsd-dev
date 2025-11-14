// 指定範囲内で特定の数の倍数を数えるプログラム
// m から n までの整数の中で p の倍数がいくつあるかを計算する

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i, m, n, p;
    int multiple_count;  // pの倍数の個数を数えるカウンター

    // ユーザーからの入力を取得
    printf("\nm, n, pの値を入力してください ex. 3,124,7\t");
    
    // 入力値のチェック
    if (scanf("%d, %d, %d", &m, &n, &p) != 3)
    {
        printf("エラー: 正しい形式で入力してください\n");
        return EXIT_FAILURE;
    }

    // 入力値の妥当性をチェック
    if (m > n)
    {
        printf("エラー: mはn以下の値を入力してください\n");
        return EXIT_FAILURE;
    }

    if (p == 0)
    {
        printf("エラー: pは0以外の値を入力してください\n");
        return EXIT_FAILURE;
    }

    // カウンターを初期化
    multiple_count = 0;
    
    // mからnまでの範囲でpの倍数を数える
    for (i = m; i <= n; i++)
    {
        if ((i % p) == 0)  // pで割り切れたらiはpの倍数
        {
            multiple_count++;
        }
    }

    // 結果を出力
    printf("\n%dから%dの間には%dの倍数が%d個あります\n", m, n, p, multiple_count);

    return EXIT_SUCCESS;
}
