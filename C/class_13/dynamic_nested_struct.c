// ネスト構造体の動的確保にフォーカスした最小サンプル
// 条件:
// - ユーザ定義ヘッダは使わない（標準ヘッダのみ）
// - 関数は main のみ
// - typedef は使わない
// 目的:
// - 親構造体の「配列」をmallocで確保
// - 各要素が持つ子構造体（ポインタ）もmallocで個別に確保
// - 最後に正しい順序でfree

#include <stdio.h>
#include <stdlib.h>

#define NAME_LEN 32        // 名前バッファ長
#define CITY_LEN 32        // 都市名バッファ長
#define PERSON_COUNT 2     // 配列要素数（学習用の固定値）

// typedef を使わずに構造体を定義
struct address {
    char city[CITY_LEN];
    int zip;
};

struct person {
    char name[NAME_LEN];
    struct address *addr; // ネスト: 子構造体を指すポインタ（個別にmalloc）
};

int main(void) {
    // 1) 親構造体の「配列」を動的に確保
    struct person *people = malloc(sizeof(struct person) * PERSON_COUNT);
    if (people == NULL) {
        fprintf(stderr, "[ERROR] people 配列のメモリ確保に失敗しました\n");
        return EXIT_FAILURE;
    }

    // 2) 各要素の子構造体を動的に確保し、デモ用の値を設定
    for (int i = 0; i < PERSON_COUNT; i++) {
        // 子構造体の確保
        people[i].addr = malloc(sizeof(struct address));
        if (people[i].addr == NULL) {
            fprintf(stderr, "[ERROR] people[%d].addr の確保に失敗\n", i);
            // 途中まで確保したメモリを開放してから終了
            for (int j = 0; j < i; j++) {
                free(people[j].addr);
            }
            free(people);
            return EXIT_FAILURE;
        }

        // 親側のフィールド設定（stdio.h の snprintf で安全に）
        snprintf(people[i].name, NAME_LEN, "Person_%d", i);

        // 子側のフィールド設定
        snprintf(people[i].addr->city, CITY_LEN, "City_%d", i);
        people[i].addr->zip = 1000 + i;
    }

    // 3) 確認のため出力
    for (int i = 0; i < PERSON_COUNT; i++) {
        printf("%d: name=%s, city=%s, zip=%d\n",
               i, people[i].name, people[i].addr->city, people[i].addr->zip);
    }

    // 4) 開放（子 → 親の順でfree）
    for (int i = 0; i < PERSON_COUNT; i++) {
        free(people[i].addr);
    }
    free(people);

    return EXIT_SUCCESS;
}
