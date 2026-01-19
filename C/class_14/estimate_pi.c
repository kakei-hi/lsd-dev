// estimate_pi.c - 乱数を使って円周率 π を推定するプログラム（教育用）
// 使い方例:
//   ビルド: clang class_14/estimate_pi.c -o class_14/estimate_pi -lm
//   実行:   ./class_14/estimate_pi を起動後、キーボードから試行回数を入力
//   引数なし。標準入力から試行回数を受け取ります。

#include <stdio.h>   // printf, scanf
#include <stdlib.h>  // strtoll, srand, rand
#include <time.h>    // time
#include <math.h>    // NAN

// Magic Number の定数化（教育用）
#define DEFAULT_TRIALS 1000000LL    // デフォルトの試行回数：100万
// 根拠: Monte Carlo の相対標準誤差 ≈ sqrt(0.2724 / N)。
// N=5e8 の場合は約 0.0023% 程度の相対標準誤差。
// 教育用途のため、長時間実行や誤入力による過負荷を防ぐ安全な上限。
#define MAX_TRIALS      500000000LL // 上限の試行回数：5億（過負荷防止)

// 乱数初期化（標準ライブラリのみを使用）
static void init_random(unsigned int seed) {
    srand(seed);
}

// Monte Carlo 法による π 推定（自己完結・ヘッダ不要）
// 単位正方形 [0,1)×[0,1) に一様乱数で点を打ち、原点中心の半径1の四分円内の割合から推定
static double estimate_pi(long long trials) {
    if (trials <= 0) {
        return NAN; // 安全対策：呼び出し側でチェック済みだが念のため
    }
    long long inside = 0;
    for (long long i = 0; i < trials; ++i) {
        double x = (double)rand() / ((double)RAND_MAX + 1.0);
        double y = (double)rand() / ((double)RAND_MAX + 1.0);
        if (x * x + y * y <= 1.0) {
            inside++;
        }
    }
    return 4.0 * (double)inside / (double)trials;
}

// 試行回数を標準入力から読み取り、入力チェックを行う関数
static long long read_trials_from_stdin(void) {
    long long trials = 0;
    printf("試行回数を入力してください（正の整数、上限 %lld）: ", (long long)MAX_TRIALS);
    if (scanf("%lld", &trials) != 1) {
        printf("[ERROR] 試行回数は正の整数で入力してください。例: 1000000\n");
        return -1;
    }
    if (trials <= 0) {
        printf("[ERROR] 試行回数は1以上にしてください。\n");
        return -1;
    }
    if (trials > MAX_TRIALS) {
        printf("[WARN] 試行回数が上限(%lld)を超えました。上限に丸めます。\n", (long long)MAX_TRIALS);
        trials = MAX_TRIALS;
    }
    return trials;
}

int main(int argc, char* argv[]) {
    // 入力のパース（試行回数）
    long long trials = read_trials_from_stdin();
    if (trials <= 0) {
        return 1; // 入力エラー
    }

    // 乱数初期化（現在時刻を種にする）
    init_random((unsigned int)time(NULL));

    // Monte Carlo 法による推定
    double pi_estimate = estimate_pi(trials);

    // 結果の表示（理論値・相対誤差は省略）
    printf("=== Monte Carlo による円周率推定 ===\n");
    printf("試行回数        : %lld\n", trials);
    printf("推定値 (実現値) : %.12f\n", pi_estimate);

    return 0;
}
