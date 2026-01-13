// 構造体「配列」の動的確保にフォーカスした最小サンプル
// 条件:
// - ユーザ定義ヘッダは使わない（標準ヘッダのみ）
// - 関数は main のみ
// - typedef は使わない
// 学習用に、確保 → 利用 → 解放 の流れだけを示します。

#include <stdio.h>
#include <stdlib.h>

#define NAME_LEN 32      // 各要素の名前バッファ長（終端\0を含めて使う設計）
#define PEOPLE_COUNT 3   // 配列の要素数（学習用に固定）

// typedef を使わずに構造体を定義
struct person {
    char *name;  // 動的確保に変更
    int age;
};

int main(void) {
    // 1) 構造体「配列」を malloc で動的に確保
    //    必要なバイト数 = 要素サイズ × 要素数
    struct person *people = malloc(sizeof(struct person) * PEOPLE_COUNT);
    if (people == NULL) {
        fprintf(stderr, "[ERROR] メモリ確保に失敗しました\n");
        return EXIT_FAILURE;
    }

    // 2) 配列を利用（ここではサンプル値を代入）
    //    各要素の name を要素ごとに動的確保してから利用する
    for (int i = 0; i < PEOPLE_COUNT; i++) {
        people[i].name = malloc(NAME_LEN);  // 固定長で確保（学習用に簡素化）
        if (people[i].name == NULL) {
            fprintf(stderr, "[ERROR] name用メモリ確保に失敗しました (i=%d)\n", i);
            // 失敗した場合：これまで確保した name を解放してから配列を解放
            for (int j = 0; j < i; j++) {
                free(people[j].name);
                people[j].name = NULL;
            }
            free(people);
            return EXIT_FAILURE;
        }
        // string.h を使わず、stdio.h の snprintf で安全に書式化
        snprintf(people[i].name, NAME_LEN, "Person_%d", i);
        people[i].age = 20 + i;
    }

    // 3) 確認のため出力
    for (int i = 0; i < PEOPLE_COUNT; i++) {
        printf("%d: name=%s, age=%d\n", i, people[i].name, people[i].age);
    }

    // 4) 使用後は必ず解放（name -> people の順に解放）
    for (int i = 0; i < PEOPLE_COUNT; i++) {
        free(people[i].name);
        people[i].name = NULL;
    }
    free(people);
    return EXIT_SUCCESS;
}
