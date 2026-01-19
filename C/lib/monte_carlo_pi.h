// monte_carlo_pi.h - 乱数を使った円周率推定ライブラリ（教育用）
// 初心者向けにコメント多めで記述します。

#ifndef MONTE_CARLO_PI_H
#define MONTE_CARLO_PI_H

#include <stddef.h>

// 乱数の初期化を行います。
// seed: 乱数の種（例: time(NULL) の返り値）
void init_random(unsigned int seed);

// Monte Carlo 法で円周率 π を推定します。
// trials: 試行回数（例: 1,000,000 などの大きな数）
// 返り値: 推定された π の値（double）
double estimate_pi(long long trials);

#endif // MONTE_CARLO_PI_H
