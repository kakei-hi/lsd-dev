//
//  Bingo
//  連続する正整数列から任意の個数の数値を
//  重複しないように抽出する
//

#include    <stdio.h>
#include    <stdlib.h>
#include    <time.h>

// 追加: ヘルパー関数のプロトタイプ宣言（単一責務・短い関数）
static int  read_range(int *m, int *n);
static int  read_count(int length, int *p);
static void initialize_array(int *array, int length, int start);
static void shuffle_array(int *box, int size);
static void print_selection(int m, int n, int *array, int p);

int main()
{
    int     m, n, p;
    int     i, length;
    int     *array;

    // 変更: 範囲入力をscanf化＋検証
    if (!read_range(&m, &n)) {
        return EXIT_FAILURE;
    }

    // 配列領域の自動確保
    length = n - m + 1; // 要素数
    array = (int*)malloc(sizeof(int) * length);
    if (array == NULL) {
        fprintf(stderr, "メモリ確保に失敗しました\n");
        return EXIT_FAILURE;
    }

    // 連続する正整数で配列を初期化（関数化）
    initialize_array(array, length, m);

    // 乱数のseedは1回だけ設定
    srand((unsigned)time(NULL));

    // 配列をシャッフル（関数名変更）
    shuffle_array(array, length);

    // 変更: 個数入力をscanf化＋検証
    if (!read_count(length, &p)) {
        free(array);
        return EXIT_FAILURE;
    }

    // 結果表示（関数化）
    print_selection(m, n, array, p);

    free(array);

    return EXIT_SUCCESS;

}

// 新規: 範囲[m, n]の入力と検証
static int read_range(int *m, int *n)
{
    // ユーザーに範囲入力を促す（カンマ区切り）
    printf("\n正整数列の範囲[m, n]を指定してください（例: 1, 10）\t");
    if (scanf("%d , %d", m, n) != 2) {
        fprintf(stderr, "\n入力エラー: m, n を整数（例: 1, 10）で指定してください\n");
        return 0;
    }
    if (*m <= 0 || *n <= 0 || *m > *n) {
        fprintf(stderr, "\n不正な範囲: m と n は正の整数で、m <= n としてください\n");
        return 0;
    }
    return 1;
}

// 新規: 個数pの入力と検証
static int read_count(int length, int *p)
{
    printf("抽出する数字の個数pを指定して下さい（例: 5）\t");
    if (scanf("%d", p) != 1) {
        fprintf(stderr, "\n入力エラー: p を整数で指定してください\n");
        return 0;
    }
    if (*p <= 0 || *p > length) {
        fprintf(stderr, "\n不正な個数: p は 1 〜 %d の範囲で指定してください\n", length);
        return 0;
    }
    return 1;
}

// 新規: 配列初期化（連続する正整数）
static void initialize_array(int *array, int length, int start)
{
    for (int i = 0; i < length; i++){
        array[i] = i + start;
    }
}

// 変更: Fisher-Yates を shuffle_array に改名し、srand 設定を削除
static void shuffle_array(int *box, int size)
{
    int     i, j, tmp;
    for ( i = size - 1; i  > 0; i-- ){
        j = rand() % (i + 1);
        tmp = box[j];
        box[j] = box[i];
        box[i] = tmp;
    }
}

// 新規: 結果表示
static void print_selection(int m, int n, int *array, int p)
{
    printf("\n区間[%d, %d]の連続する正整数列から%d個の数値を重複なく選択する\n", m, n, p);
    printf("(");
    for (int i = 0; i < p; i ++ ){
        if ( i != p - 1){
            printf("%d, ",array[i]);
        }
        else {
            printf("%d",array[i]);
        }
    }
    printf(")\n");
}

