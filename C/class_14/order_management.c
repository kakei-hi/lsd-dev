#include <stdio.h>
#include <stdlib.h>
#include <string.h>  // 動的文字列操作に必要

#define NAME_LEN 50  // 入力用一時バッファ長（実際のnameは動的確保）
// 49の根拠: scanfの幅指定は「最大読み取り文字数」。NAME_LENは50のため、終端文字('\0')を1文字分確保する目的で49(=NAME_LEN-1)を使用する。

// 要件1: 構造体の定義（typedefは使用しない）
struct Item {
    char *name;  // 動的確保に変更
    int price;
};

struct Order {
    int orderId;
    struct Item *items;    // 商品構造体配列へのポインタ
    int itemCount;         // 商品の個数
};

// 関数の前方宣言
static void free_item_names(struct Order *order);
static void free_orders_partial(struct Order *orders, int count);
static int input_order_count(void);
static int input_single_item(struct Item *item, int item_index);
static int input_single_order(struct Order *order, int order_index);
static int input_all_orders(struct Order *orders, int order_count);
static int calculate_order_total(const struct Order *order);
static void display_all_orders(const struct Order *orders, int order_count);
static void free_all_orders(struct Order *orders, int order_count);

// 各注文内のnameポインタを安全に解放
static void free_item_names(struct Order *order) {
    if (order == NULL || order->items == NULL) return;
    for (int j = 0; j < order->itemCount; j++) {
        free(order->items[j].name);
    }
}

// 部分的に確保済みの注文配列を安全に解放するユーティリティ
static void free_orders_partial(struct Order *orders, int count) {
    if (orders == NULL) return;
    for (int i = 0; i < count; i++) {
        if (orders[i].items != NULL) {
            free_item_names(&orders[i]);
            free(orders[i].items);
        }
    }
    free(orders);
}

// 注文数の入力を行う関数
// 戻り値: 成功時は注文数、失敗時は-1
static int input_order_count() {
    int count;
    printf("総注文数を入力してください: ");
    if (scanf("%d", &count) != 1 || count <= 0) {
        fprintf(stderr, "入力が不正です。\n");
        return -1;
    }
    return count;
}

// 単一の注文データを入力する関数
// 戻り値: 成功時は0、失敗時は-1
static int input_single_order(struct Order *order, int order_index) {
    printf("\n[注文 %d]\n", order_index + 1);
    printf("注文番号: ");
    if (scanf("%d", &order->orderId) != 1) {
        fprintf(stderr, "入力が不正です。\n");
        return -1;
    }

    int item_count;
    printf("商品の種類数: ");
    if (scanf("%d", &item_count) != 1 || item_count <= 0) {
        fprintf(stderr, "入力が不正です。\n");
        return -1;
    }
    order->itemCount = item_count;

    // 商品配列の確保
    order->items = (struct Item *)calloc(item_count, sizeof(struct Item));
    if (order->items == NULL) {
        fprintf(stderr, "メモリ確保に失敗しました。\n");
        return -1;
    }

    // 各商品の入力
    for (int j = 0; j < item_count; j++) {
        if (input_single_item(&order->items[j], j) != 0) {
            return -1;
        }
    }

    return 0;
}

// 単一の商品データを入力する関数
// 戻り値: 成功時は0、失敗時は-1
static int input_single_item(struct Item *item, int item_index) {
    printf("  商品名%d: ", item_index + 1);
    char temp_name[NAME_LEN];
    // 49の根拠: temp_nameは長さNAME_LEN(50)。%49sは最大49文字のみ読み取り、残り1文字をNUL終端に充当してバッファオーバーランを防ぐ。
    if (scanf("%49s", temp_name) != 1) {
        fprintf(stderr, "入力が不正です。\n");
        return -1;
    }

    // 商品名の動的確保
    size_t len = strlen(temp_name);
    item->name = (char *)malloc(len + 1);
    if (item->name == NULL) {
        fprintf(stderr, "メモリ確保に失敗しました。\n");
        return -1;
    }
    strcpy(item->name, temp_name);

    // 単価の入力
    printf("  単価%d: ", item_index + 1);
    if (scanf("%d", &item->price) != 1) {
        fprintf(stderr, "入力が不正です。\n");
        return -1;
    }
    if (item->price < 0) {
        fprintf(stderr, "単価は0以上にしてください。\n");
        return -1;
    }

    return 0;
}

// すべての注文データを入力する関数
// 戻り値: 成功時は0、失敗時は-1
static int input_all_orders(struct Order *orders, int order_count) {
    for (int i = 0; i < order_count; i++) {
        if (input_single_order(&orders[i], i) != 0) {
            free_orders_partial(orders, i + 1);
            return -1;
        }
    }
    return 0;
}

// 単一注文の合計金額を計算する関数
static int calculate_order_total(const struct Order *order) {
    int total = 0;
    for (int j = 0; j < order->itemCount; j++) {
        total += order->items[j].price;
    }
    return total;
}

// すべての注文一覧を表示する関数
static void display_all_orders(const struct Order *orders, int order_count) {
    printf("\n--- 注文一覧 ---\n");
    for (int i = 0; i < order_count; i++) {
        int total = calculate_order_total(&orders[i]);
        printf("注文番号 %d: 合計 %d円\n", orders[i].orderId, total);
    }
}

// すべてのメモリを解放する関数
static void free_all_orders(struct Order *orders, int order_count) {
    for (int i = 0; i < order_count; i++) {
        free_item_names(&orders[i]);
        free(orders[i].items);
    }
    free(orders);
}

int main() {
    // ステップ1: 注文数の入力
    int order_count = input_order_count();
    if (order_count < 0) {
        return EXIT_FAILURE;
    }

    // ステップ2: 注文配列の動的確保
    struct Order *orders = (struct Order *)malloc(sizeof(struct Order) * order_count);
    if (orders == NULL) {
        fprintf(stderr, "メモリ確保に失敗しました。\n");
        return EXIT_FAILURE;
    }

    // ステップ3: すべての注文データを入力
    if (input_all_orders(orders, order_count) != 0) {
        return EXIT_FAILURE;
    }

    // ステップ4: 注文一覧を表示
    display_all_orders(orders, order_count);

    // ステップ5: メモリを解放
    free_all_orders(orders, order_count);
    printf("メモリを解放して終了します。\n");

    return EXIT_SUCCESS;
}
