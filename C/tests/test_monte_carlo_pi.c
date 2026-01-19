// test_monte_carlo_pi.c - Monte Carlo π推定の簡易テスト（教育用）
// 実行例:
//   ビルド: clang tests/test_monte_carlo_pi.c lib/monte_carlo_pi.c -o tests/test_monte_carlo_pi -lm
//   実行:   ./tests/test_monte_carlo_pi

#include <stdio.h>
#include <time.h>
#include <math.h>
#include "../lib/monte_carlo_pi.h"

static void run_case(long long trials) {
    double pi_estimate = estimate_pi(trials);
    double pi_theory = acos(-1.0);
    double relative_error = (pi_theory == 0.0) ? 0.0 : (pi_estimate - pi_theory) / pi_theory;
    if (relative_error < 0) relative_error = -relative_error;

    printf("[試行回数:%lld] 推定値=%.8f 理論=%.8f 相対誤差=%.3e\n",
           trials, pi_estimate, pi_theory, relative_error);
}

int main(void) {
    init_random((unsigned int)time(NULL));
    // 収束の様子を見るために試行回数を増やしていく
    run_case(10000LL);
    run_case(100000LL);
    run_case(1000000LL);
    return 0;
}
