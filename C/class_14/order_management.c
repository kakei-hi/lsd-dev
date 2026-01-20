#include <stdio.h>
#include <stdlib.h>

#define NAME_LEN 50  // 文字列長の定数化（Magic Number回避）

// 要件1: 構造体の定義（typedefは使用しない）
struct Item {
    char name[NAME_LEN];
    int price;
};

struct Order {
    int orderId;
    struct Item *items;    // 商品構造体配列へのポインタ
    int itemCount;         // 商品の個数
};

// 部分的に確保済みの注文配列を安全に解放するユーティリティ
static void free_orders_partial(struct Order *orders, int count) {
    if (orders == NULL) return;
    for (int i = 0; i < count; i++) {
        free(orders[i].items);
    }
    free(orders);
}

int main() {
    int n, m;
    struct Order *orders = NULL;

    // 要件2: 注文配列の動的確保
    printf("総注文数を入力してください: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "入力が不正です。\n");
        return EXIT_FAILURE;
    }

    orders = (struct Order *)malloc(sizeof(struct Order) * n);
    if (orders == NULL) {
        fprintf(stderr, "メモリ確保に失敗しました。\n");
        return EXIT_FAILURE;
    }

    // 要件3: 各注文内の商品配列の動的確保とデータ入力
    for (int i = 0; i < n; i++) {
        printf("\n[注文 %d]\n", i + 1);
        printf("注文番号: ");
        if (scanf("%d", &orders[i].orderId) != 1) {
            fprintf(stderr, "入力が不正です。\n");
            free_orders_partial(orders, i);
            return EXIT_FAILURE;
        }

        printf("商品の種類数: ");
        if (scanf("%d", &m) != 1 || m <= 0) {
            fprintf(stderr, "入力が不正です。\n");
            free_orders_partial(orders, i);
            return EXIT_FAILURE;
        }
        orders[i].itemCount = m;

        // ネストされた構造体配列の確保
        orders[i].items = (struct Item *)malloc(sizeof(struct Item) * m);
        if (orders[i].items == NULL) {
            fprintf(stderr, "メモリ確保に失敗しました。\n");
            free_orders_partial(orders, i);
            return EXIT_FAILURE;
        }

        for (int j = 0; j < m; j++) {
            printf("  商品名%d: ", j + 1);
            if (scanf("%49s", orders[i].items[j].name) != 1) {
                fprintf(stderr, "入力が不正です。\n");
                free_orders_partial(orders, i + 1);
                return EXIT_FAILURE;
            }
            printf("  単価%d: ", j + 1);
            if (scanf("%d", &orders[i].items[j].price) != 1) {
                fprintf(stderr, "入力が不正です。\n");
                free_orders_partial(orders, i + 1);
                return EXIT_FAILURE;
            }
            if (orders[i].items[j].price < 0) {
                fprintf(stderr, "単価は0以上にしてください。\n");
                free_orders_partial(orders, i + 1);
                return EXIT_FAILURE;
            }
        }
    }

    // 要件4: 情報の表示と計算
    printf("\n--- 注文一覧 ---\n");
    for (int i = 0; i < n; i++) {
        int total = 0;
        for (int j = 0; j < orders[i].itemCount; j++) {
            total += orders[i].items[j].price;
        }
        printf("注文番号 %d: 合計 %d円\n", orders[i].orderId, total);
    }

    // 要件5: メモリの解放
    for (int i = 0; i < n; i++) {
        free(orders[i].items);
    }
    free(orders);

    printf("メモリを解放して終了します。\n");

    return EXIT_SUCCESS;
}
