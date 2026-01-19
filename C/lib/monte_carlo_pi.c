// monte_carlo_pi.c - 乱数を使った円周率推定ライブラリ（教育用）
// Monte Carlo 法で π を求めるシンプルな実装です。

#include <stdlib.h> // rand, srand, RAND_MAX
#include "monte_carlo_pi.h"

// 乱数の初期化を行う関数
void init_random(unsigned int seed) {
    // srand は C 標準ライブラリの乱数の種を設定します
    srand(seed);
}

// Monte Carlo 法で π を推定する関数
double estimate_pi(long long trials) {
    // 入力チェック：試行回数が 1 以下なら 0.0 を返す
    if (trials <= 0) {
        return 0.0;
    }

    long long inside_count = 0; // 円（半径1）の内側に入った点の数

    // [0,1) の一様乱数を2つ生成して点 (x, y) を作り、
    // 原点を中心とする半径1の円の内側（x^2 + y^2 <= 1）に入るかを判定します。
    for (long long i = 0; i < trials; i++) {
        double x = (double)rand() / (double)RAND_MAX;
        double y = (double)rand() / (double)RAND_MAX;
        double r2 = x * x + y * y; // 原点からの距離の二乗
        if (r2 <= 1.0) {
            inside_count++;
        }
    }

    // 単位正方形上の点が円の内側に入る割合を p とすると、
    // 円の面積（π * 1^2）/ 正方形の面積（1 * 1） = p より、π ≈ 4 * p となります。
    double ratio = (double)inside_count / (double)trials;
    return 4.0 * ratio;
}
