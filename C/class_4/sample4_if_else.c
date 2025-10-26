/*
 * if-elseの使い方を学ぶためのサンプルプログラム
 * 点数を入力して、成績を判定する簡単なプログラム
 */

#include <stdio.h>

int main(void) {
    int score; // 点数を格納する変数

    // ユーザーに点数の入力を促す
    printf("点数を入力してください（0-100）: ");
    scanf("%d", &score);

    // 入力値のチェック
    if (score < 0 || score > 100) {
        printf("エラー: 点数は0から100の間で入力してください。\n");
        return 1;  // エラーの場合はプログラムを終了
    }

    // if-elseを使った成績判定
    if (score >= 90) {
        printf("評価: 秀（S）\n");
    } else if (score >= 80) {
        printf("評価: 優（A）\n");
    } else if (score >= 70) {
        printf("評価: 良（B）\n");
    } else if (score >= 60) {
        printf("評価: 可（C）\n");
    } else {
        printf("評価: 不可（F）\n");
        printf("もう少し頑張りましょう！\n");
    }

    return 0;
}
