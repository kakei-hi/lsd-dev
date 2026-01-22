// class_14/leap_year.c - 閏年判定と次の10回分の閏年列挙（単一ファイル版）
// 教育用プロジェクト方針に沿い、初心者が読みやすい構成を意識しています。
// ファイルはこの1本のみ（ヘッダーやテストは作成しない）。

#include <stdio.h>
#include <stdlib.h>  // EXIT_SUCCESS, EXIT_FAILURE, strtol などの標準ライブラリ関数を使用するため
#include <string.h>  // strcspn 関数（文字列から改行を除去する処理）を使用するため
#include <errno.h>   // errno 変数（strtol のエラー判定）を使用するため
#include <stdbool.h> // bool, true, false 型（閏年判定の戻り値）を使用するため

// 定数（Magic Number回避）
#define MIN_YEAR 1
#define MAX_YEAR 100000
#define LEAP_YEARS_TO_LIST 10

// 関数: is_leap_year
// 目的: 渡された西暦yearが閏年かどうかを判定する
// 仕様: 400で割り切れる年は閏年、100で割り切れる年は平年、4で割り切れる年は閏年
// 戻り値: true(閏年) または false(閏年ではない)
static bool is_leap_year(int year){

    if ((year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0))){
        return true;
    }
    else{
        return false;
    }

}
// 関数: list_next_leap_years
// 目的: start_yearの「次」から見つかる閏年をcount件、out_yearsに格納する
// 注意: start_year自身が閏年でも、それは含めず次から数える
// 戻り値: 実際に格納した件数（通常はcount）。入力不正時は0。
static int list_next_leap_years(int start_year, int count, int *out_years) {
    if (out_years == NULL || count <= 0) {
        return 0;
    }

    int found = 0;
    int year = start_year + 1; // 起点年の「次」から開始
    bool leap = false;         // 閏年判定の結果を保持
    while (found < count) {
        leap = is_leap_year(year);
        if (leap) {
            out_years[found] = year;
            found++;
        }
        year++;
    }
    return found;
}

// 関数: read_year_from_stdin
// 目的: 標準入力から安全に年を読み取り、範囲チェックを行う
// 成功時: *out_yearに値を設定し1を返す
// 失敗時: エラーメッセージを表示し0を返す
static int read_year_from_stdin(int *out_year) {
    char buffer[128];

    printf("西暦（整数）を入力してください: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "入力の読み取りに失敗しました。\n");
        return 0;
    }
    // 改行を除去
    buffer[strcspn(buffer, "\n")] = '\0';

    // 文字列を整数に変換（安全な方法: strtol）
    errno = 0;
    char *endptr = NULL;
    long value = strtol(buffer, &endptr, 10);

    if (errno != 0) {
        perror("数値変換エラー");
        return 0;
    }
    if (endptr == buffer || *endptr != '\0') {
        fprintf(stderr, "整数以外の文字が含まれています: '%s'\n", buffer);
        return 0;
    }
    if (value < MIN_YEAR || value > MAX_YEAR) {
        fprintf(stderr, "年は %d 以上 %d 以下で入力してください。\n", MIN_YEAR, MAX_YEAR);
        return 0;
    }

    *out_year = (int)value;
    return 1;
}

int main(void) {
    int year = 0;
    if (!read_year_from_stdin(&year)) {
        return EXIT_FAILURE; // 入力不正
    }

    // 閏年判定結果の表示（bool変数を使用）
    bool is_leap = is_leap_year(year);
    if (is_leap) {
        printf("%d年は閏年です。\n", year);
    } else {
        printf("%d年は閏年ではありません。\n", year);
    }

    // 次の10回分の閏年を列挙して表示
    int years[LEAP_YEARS_TO_LIST];
    int wrote = list_next_leap_years(year, LEAP_YEARS_TO_LIST, years);

    printf("次の%d回分の閏年: ", LEAP_YEARS_TO_LIST);
    for (int i = 0; i < wrote; ++i) {
        printf("%d%s", years[i], (i + 1 == wrote) ? "" : " ");
    }
    printf("\n");

    return EXIT_SUCCESS;
}
