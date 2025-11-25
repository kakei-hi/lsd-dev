// local_static_demo.c - 局部静的変数の実例集
// ポイント:
// - 局部静的変数(static)は「関数の中に定義」されるが，
//   値は関数を抜けても保持され，次回呼び出し時に引き継がれる．
// - スコープはその関数内に限定され，他所から直接は触れない．
// - 状態の保存，初期化の一度きり実行，連番発行などに有効．

#include <stdio.h>

// =========================
// 定数（Magic Number の排除）
// =========================
#define START_ID 1
#define MAX_ID 10000

// =========================
// 関数プロトタイプ宣言
// =========================
int generate_unique_id(void);
int count_function_calls(void);
int add_running_total(int value);
void initialize_once(void);

// =========================
// 関数: generate_unique_id
// 目的: 呼び出すたびに連番IDを返す（関数内の状態を保持）
// 説明: static変数 current_id は関数を抜けても値を保持するので，
//       次の呼び出しで前回の続きからIDを発行できる．
// 責務: 連番の発行のみ（単一責務）
// =========================
int generate_unique_id(void) {
    static int current_id = START_ID; // 初回呼び出し時のみ初期化

    // 上限を超えたら先頭へ戻す（教育用の単純化）
    if (current_id > MAX_ID) {
        current_id = START_ID;
    }

    // 返却後に次回用へインクリメント
    return current_id++;
}

// =========================
// 関数: count_function_calls
// 目的: この関数が何回呼ばれたかを返す
// 説明: static変数 call_count が回数をずっと覚えている．
// =========================
int count_function_calls(void) {
    static int call_count = 0; // 初回のみ0で初期化
    call_count++;
    return call_count;
}

// =========================
// 関数: add_running_total
// 目的: 累積合計を管理し，現在の合計値を返す
// 説明: 合計値 total をstaticで保持し，呼び出し毎に加算していく．
// =========================
int add_running_total(int value) {
    static int total = 0; // これまでの合計を保持
    total += value;
    return total;
}

// =========================
// 関数: initialize_once
// 目的: 初回だけ初期化処理を実行し，2回目以降はスキップする
// 説明: 「一度だけの初期化」にも局部静的変数は便利
// =========================
void initialize_once(void) {
    static int is_initialized = 0; // 0:未初期化,，1:初期化済み
    if (!is_initialized) {
        // 初回だけ実行したい処理
        printf("[initialize_once] 初回だけの準備を実行しました。\n");
        is_initialized = 1;
    } else {
        printf("[initialize_once] 既に初期化済みです。\n");
    }
}

// =========================
// 関数: main
// 目的: 各サンプル関数を呼び出して挙動を確認する
// =========================
int main(void) {
    printf("=== 局部静的変数のデモ ===\n");

    // 1) 連番IDの発行
    printf("-- generate_unique_id を3回呼びます\n");
    for (int i = 0; i < 3; i++) {
        int id = generate_unique_id();
        printf("発行されたID: %d\n", id);
    }

    // 2) 関数の呼び出し回数カウント
    printf("-- count_function_calls を3回呼びます\n");
    for (int i = 0; i < 3; i++) {
        int called = count_function_calls();
        printf("呼び出し回数: %d\n", called);
    }

    // 3) 累積合計
    printf("-- add_running_total に値を渡して累積合計を観察します\n");
    // 配列は使わず、個別に呼び出して表示
    int current_total = add_running_total(5);
    printf("入力: %d -> 現在の合計: %d\n", 5, current_total);
    current_total = add_running_total(10);
    printf("入力: %d -> 現在の合計: %d\n", 10, current_total);
    current_total = add_running_total(-2);
    printf("入力: %d -> 現在の合計: %d\n", -2, current_total);
    current_total = add_running_total(7);
    printf("入力: %d -> 現在の合計: %d\n", 7, current_total);

    // 4) 初期化の一度きり
    printf("-- initialize_once を2回呼びます\n");
    initialize_once();
    initialize_once();

    printf("=== デモ終了 ===\n");

    // 正常終了
    return 0;
}

/*
テストの提案（教育用）：
- 連番ID: 連続呼び出しで 1,2,3... と増えることを標準出力で確認。
- 呼び出し回数: 最初の戻り値が1、以降 2,3... と増えることを確認。
- 累積合計: 期待する合計（5 -> 15 -> 13 -> 20）になることを確認。
- 初期化一度きり: 1回目は「初回だけの準備」、2回目は「既に初期化済み」と表示されること。
*/
