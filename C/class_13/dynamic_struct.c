#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Magic Number を定数化
#define NAME_MAX_LEN 32
#define MAX_AGE 120

// typedef は使わずに構造体を定義
struct person {
    // name を動的に確保するためポインタに変更
    char *name;
    int age;
};

int main(void) {
    // 構造体を動的に1つ確保
    struct person *p = malloc(sizeof(struct person));
    if (p == NULL) {
        fprintf(stderr, "[ERROR] メモリ確保に失敗しました\n");
        return EXIT_FAILURE;
    }

    // ゼロ初期化（安全側）
    memset(p, 0, sizeof(*p));

    // デモ用の値（本来は入力などから取得）
    const char *input_name = "Alice";
    int input_age = 20;

    // 名前用のメモリを動的に確保（最大 NAME_MAX_LEN まで）
    size_t src_len = strlen(input_name);
    size_t name_len = src_len;
    if (src_len > NAME_MAX_LEN) {
        name_len = NAME_MAX_LEN;
    }
    p->name = malloc(name_len + 1);
    if (p->name == NULL) {
        fprintf(stderr, "[ERROR] 名前用メモリの確保に失敗しました\n");
        free(p);
        return EXIT_FAILURE;
    }
    // 文字列を安全にコピーして終端を保証
    memcpy(p->name, input_name, name_len);
    p->name[name_len] = '\0';

    // 年齢の簡単な範囲チェック
    if (input_age < 0 || input_age > MAX_AGE) {
        fprintf(stderr, "[ERROR] 年齢が不正です（0..%d）\n", MAX_AGE);
        free(p->name);
        free(p);
        return EXIT_FAILURE;
    }
    p->age = input_age;

    // 結果の表示
    printf("Name: %s\n", p->name);
    printf("Age : %d\n", p->age);

    // 必ず解放（name → 構造体の順）
    free(p->name);
    free(p);
    return EXIT_SUCCESS;
}
