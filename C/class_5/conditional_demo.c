/*
 * conditional_demo.c
 * 条件分岐（if と switch）の使い分けを学ぶためのサンプル
 * 制約: main 関数のみを使用し、他の関数は使用しない
 * 初心者向けにコメント多めで説明しています。
 */

#include <stdio.h>

int main(void) {
    /*
     * Part 1: if / else-if の例
     *  - 範囲（不等号）に基づく判定は if-else が自然
     *  - ここでは点数(score)を 0-100 の範囲で評価に変換する
     */
    int score = -1;
    printf("=== if/else の例: 点数から評価を決定 ===\n");
    printf("整数の点数 (0-100) を入力してください: ");
    if (scanf("%d", &score) != 1) {
        /* 入力が整数でない場合の簡単なエラー処理 */
        printf("入力エラー: 整数を入力してください\n");
        return 1;
    }

    /* 範囲チェックを先に行うことで不正入力への対応を明確にする */
    if (score < 0 || score > 100) {
        printf("範囲外の点数です: %d\n", score);
    } else if (score >= 90) {
        printf("評価: A (90-100)\n");
    } else if (score >= 80) {
        printf("評価: B (80-89)\n");
    } else if (score >= 70) {
        printf("評価: C (70-79)\n");
    } else if (score >= 60) {
        printf("評価: D (60-69)\n");
    } else {
        printf("評価: F (0-59)\n");
    }

    /*
     * 解説（if を使う理由）:
     * - 範囲比較（例えば >= や <）を順番に評価できる
     * - 条件が重なりやすい場合は順序に注意（上位の条件を先に）
     * - 複雑な論理式（&&, ||）も扱える
     */

    /* 区切り */
    printf("\n");

    /*
     * Part 2: switch の例
     *  - 整数や列挙値など「値が等しいか」を判定するのに向く
     *  - case ごとに明確に分岐が並ぶため可読性が高い
     *  - 範囲判定や不等号には向かない（case は定数比較）
     */
    int option = -1;
    printf("=== switch の例: メニュー選択 (整数) ===\n");
    printf("メニュー番号を入力してください (1: 新規, 2: 表示, 3: 削除, 4: 終了): ");
    if (scanf("%d", &option) != 1) {
        printf("入力エラー: 整数を入力してください\n");
        return 1;
    }

    switch (option) {
        case 1:
            printf("新規作成を選びました。\n");
            break;
        case 2:
            printf("表示を選びました。\n");
            break;
        case 3:
            printf("削除を選びました。\n");
            break;
        case 4:
            printf("終了を選びました。\n");
            break;
        default:
            /* default はどの case にも当てはまらないときに実行される */
            printf("不正なメニュー番号です: %d\n", option);
            break;
    }

    /*
     * 補足:
     * - switch は case が多い分岐で見通しが良い
     * - enum を使った状態判定やメニュー、キー入力の処理に適している
     * - ただし case に範囲を書くことはできない（C言語の場合）
     */

    /* まとめを表示 */
    printf("\nまとめ:\n");
    printf("- if: 範囲判定・複雑な論理式に強い（不等号や &&, || を使う）\n");
    printf("- switch: 等値比較が複数ある場面で読みやすく整理しやすい（整数・列挙）\n");
    printf("- 実務では両方を目的に応じて使い分ける（可読性と正確さを優先）\n");

    return 0;
}
