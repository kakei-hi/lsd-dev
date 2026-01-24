// dice_two_7.c - 7面サイコロ2個の出目合計の分布を表示する
// 教育用: 初心者向けにコメント多めで記述
// 要件:
// 1) (1..7) の目が等確率で出るサイコロを2つ振る
// 2) 出目合計の出現数と相対出現率（実現値・理論値）を表示

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// --------- 設定用定数（Magic Numberの排除） ---------
#define SIDES 7            // サイコロの面数（1..7）
#define MIN_SUM 2          // 合計の最小値（1+1）
#define MAX_SUM (2 * SIDES)// 合計の最大値（7+7）
#define DEFAULT_TRIALS 100000 // 入力不正時のデフォルト試行回数

// --------- サイコロ（等確率）を1回振って目を返す ---------
int roll_die(int sides) {
    unsigned int r = (unsigned int)rand();   
    return (int)(r % sides) + 1; // 1..sides の目
}

// --------- 理論的な組合せ数（合計sumが出る通り数）を返す ---------
// 1..SIDES の2つの和が sum になる組の数
int theoretical_count_for_sum(int sum) {
    if (sum < MIN_SUM || sum > MAX_SUM) return 0;
    // 和の分布は三角形分布: 2..(SIDES+1) で増加、(SIDES+2)..(2*SIDES) で減少
    int midpoint = SIDES + 1;
    if (sum <= midpoint) {
        return sum - 1; // 例: sum=2 ->1通り, sum=3 ->2通り ...
    } else {
        return (2 * SIDES + 1) - sum; // 例: sum=14 ->1通り
    }
}

// --------- 入力（試行回数）を取得して安全に整数へ ---------
// 標準入力から回数を読み取り、0以下ならデフォルト値に置換
int read_trials_from_stdin(void) {
    char buf[256];
    long trials = 0;
    printf("試行回数を入力してください（例: 100000）: ");
    if (fgets(buf, sizeof(buf), stdin) != NULL) {
        char *endptr = NULL;
        trials = strtol(buf, &endptr, 10);
        if (endptr == buf) {
            // 数字が読み取れなかった
            fprintf(stderr, "数値入力を解釈できません。%d 回で実行します。\n", DEFAULT_TRIALS);
            trials = DEFAULT_TRIALS;
        }
    } else {
        // 入力失敗時
        fprintf(stderr, "入力に失敗しました。%d 回で実行します。\n", DEFAULT_TRIALS);
        trials = DEFAULT_TRIALS;
    }

    if (trials <= 0) {
        fprintf(stderr, "0以下の値が指定されたため、%d 回で実行します。\n", DEFAULT_TRIALS);
        trials = DEFAULT_TRIALS;
    }
    // 上限は任意だが、極端に大きい値への誤入力を簡易防御
    if (trials > 100000000) {
        fprintf(stderr, "指定が大きすぎるため、%d 回に制限します。\n", DEFAULT_TRIALS);
        trials = DEFAULT_TRIALS;
    }
    return (int)trials;
}

// --------- 分布表の表示（実現値・理論値） ---------
void print_distribution(const int counts[], int trials) {
    // 見出し
    printf("\n=== 7面サイコロ2個の合計の分布 ===\n");
    printf("試行回数: %d\n", trials);
    printf("合計\t出現数\t相対出現率(実現)\t相対出現率(理論)\t差分\n");

    int total_count = 0;
    for (int s = MIN_SUM; s <= MAX_SUM; ++s) {
        total_count += counts[s];
        int theo_count = theoretical_count_for_sum(s);
        double empirical = (double)counts[s] / (double)trials;
        double theoretical = (double)theo_count / (double)(SIDES * SIDES);
        double diff = empirical - theoretical;
        printf("%2d\t%7d\t%18.6f\t%18.6f\t%+.6f\n", s, counts[s], empirical, theoretical, diff);
    }
    // 合計の確認（安全のため）
    printf("合計出現数の検算: %d (期待: %d)\n", total_count, trials);
}

int main(void) {
    // 乱数の初期化（現在時刻を種にする）
    srand((unsigned int)time(NULL));

    // 試行回数を読み取る
    int trials = read_trials_from_stdin();

    // 合計ごとのカウント配列を用意（インデックスは合計値をそのまま使用）
    int counts[MAX_SUM + 1];
    for (int i = 0; i <= MAX_SUM; ++i) counts[i] = 0;

    // 実験の実行: 2つのフェアな7面サイコロを振る
    for (int t = 0; t < trials; ++t) {
        int d1 = roll_die(SIDES);
        int d2 = roll_die(SIDES);
        int sum = d1 + d2; // 合計は 2..14
        counts[sum]++;
    }

    // 分布表を表示（実現値・理論値）
    print_distribution(counts, trials);
    return 0;
}
