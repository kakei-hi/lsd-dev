// capital_lookup.c - 国名から首都名を検索するプログラム（教育用）
// 要件:
//  1. 入力された国の首都名を返す
//  2. データにない国名は「データに見当たらない」旨を表示
//  3. ユーザー定義ヘッダは使用しない（標準ヘッダのみ）
// 備考:
//  - 入力は大文字・小文字を区別しない（"Japan" でも可）
//  - 初心者向けに、短い関数・コメント多め・安全な入力読み取り

#include <ctype.h>   // toupper
#include <stdio.h>   // printf, fgets
#include <string.h>  // strlen, strcmp
#include <stdlib.h>  // EXIT_SUCCESS, EXIT_FAILURE

// Magic Number の定数化
#define MAX_INPUT_LEN 128  // 入力バッファの最大長（改行含む）

// 国名と首都名のペア（要件で与えられた 5 件）
struct country_capital {
    const char* country;  // 国名（大文字表記）
    const char* capital;  // 首都名（大文字表記）
};

static const struct country_capital DATA[] = {
    {"JAPAN",  "TOKYO"},
    {"FRANCE", "PARIS"},
    {"UK",     "LONDON"},
    {"EGYPT",  "CAIRO"},
    {"CHILE",  "SANTIAGO"},
};

static const size_t DATA_COUNT = sizeof(DATA) / sizeof(DATA[0]);

// 改行を取り除く（末尾が'\n'なら'\0'に置き換える）
static void trim_newline(char* s) {
    if (s == NULL) return;
    size_t n = strlen(s);
    if (n > 0 && s[n - 1] == '\n') {
        s[n - 1] = '\0';
    }
}

// 文字列を大文字化（ASCII想定）。破壊的に変換する。
static void to_upper_ascii(char* s) {
    if (s == NULL) return;
    for (; *s != '\0'; ++s) {
        unsigned char c = (unsigned char)*s;
        *s = (char)toupper(c);  // <ctype.h>
    }
}

// 国名（大文字表記）で首都を検索。見つかれば capital を返し、なければ NULL。
static const char* find_capital(const char* upper_country) {
    if (upper_country == NULL) return NULL;
    for (size_t i = 0; i < DATA_COUNT; ++i) {
        if (strcmp(upper_country, DATA[i].country) == 0) {
            return DATA[i].capital;
        }
    }
    return NULL;
}

int main(void) {
    char buf[MAX_INPUT_LEN];

    printf("国名を入力してください（例: JAPAN）: ");
    if (fgets(buf, sizeof(buf), stdin) == NULL) {
        // EOF あるいはエラー
        printf("[ERROR] 入力を読み取れませんでした。\n");
        return EXIT_FAILURE;
    }

    trim_newline(buf);

    // 空文字チェック
    if (buf[0] == '\0') {
        printf("[ERROR] 国名が空です。\n");
        return EXIT_FAILURE;
    }

    // 大文字・小文字を無視するため、大文字化
    to_upper_ascii(buf);

    const char* capital = find_capital(buf);
    if (capital != NULL) {
        // 見つかった場合は首都名を表示
        printf("%s の首都は %s です。\n", buf, capital);
        return EXIT_SUCCESS;
    }

    // 見つからなかった場合のメッセージ（要件 2）
    printf("%s はデータに見当たりません。\n", buf);
    return EXIT_SUCCESS;
}
