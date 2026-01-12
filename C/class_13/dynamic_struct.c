#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Magic Number を定数化
#define NAME_MAX_LEN 32
#define MAX_AGE 120

// typedef は使わずに構造体を定義
struct person {
    char name[NAME_MAX_LEN + 1]; // 末尾の '\0' 用に +1
    int age;
};

int main(void) {
    // 構造体を動的に1つ確保
    struct person *p = (struct person *)malloc(sizeof(struct person));
    if (p == NULL) {
        fprintf(stderr, "[ERROR] メモリ確保に失敗しました\n");
        return EXIT_FAILURE;
    }

    // ゼロ初期化（安全側）
    memset(p, 0, sizeof(*p));

    // デモ用の値（本来は入力などから取得）
    const char *input_name = "Alice";
    int input_age = 20;

    // 名前を安全にコピー（終端保証）
    strncpy(p->name, input_name, NAME_MAX_LEN);
    p->name[NAME_MAX_LEN] = '\0';

    // 年齢の簡単な範囲チェック
    if (input_age < 0 || input_age > MAX_AGE) {
        fprintf(stderr, "[ERROR] 年齢が不正です（0..%d）\n", MAX_AGE);
        free(p);
        return EXIT_FAILURE;
    }
    p->age = input_age;

    // 結果の表示
    printf("Name: %s\n", p->name);
    printf("Age : %d\n", p->age);

    // 必ず解放
    free(p);
    return EXIT_SUCCESS;
}
