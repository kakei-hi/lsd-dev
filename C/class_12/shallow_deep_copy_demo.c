// shallow_deep_copy_demo.c - Shallow Copy と Deep Copy の違いデモ
// 目的:
//  1. 配列(スタック上) + ポインタでの浅い/深いコピーの違い
// 規約: 命名はスネークケース、コメント多め、Magic Number は定数化

#include <stdio.h>

#define NAME_TEXT "take"
#define ARRAY_COPY_LEN (sizeof(NAME_TEXT)) // 終端'\0'込み

// 1) 配列 + ポインタでの浅い/深いコピー
void demonstrate_array_shallow_deep(void) {
    char original[] = NAME_TEXT;      // スタック上の配列 (書き換え可能)
    char *shallow = original;         // 浅いコピー: アドレスだけ共有
    char deep[ARRAY_COPY_LEN];        // 深いコピー: 内容を別領域に複製

    // 手動コピー (終端込み)
    for (size_t i = 0; i < ARRAY_COPY_LEN; i++) {
        deep[i] = original[i];
    }

    printf("=== 配列 + ポインタの浅い/深いコピー ===\n");
    printf("[コピー直後]\n");
    printf("  original(先頭)  = %p, 値=%s\n", (void *)&original[0], original);
    printf("  shallow(値)     = %p, 参照先=%s\n", (void *)shallow, shallow);
    printf("  deep(先頭)      = %p, 値=%s\n", (void *)&deep[0], deep);

    // original を変更して影響範囲を観察
    original[0] = 'c';

    printf("[original[0] を 'c' に変更後]\n");
    printf("  original        = %s\n", original);
    printf("  shallow         = %s  (同じ領域を参照するためoriginalの変更が反映される)\n", shallow);
    printf("  deep            = %s  (別領域なのでoriginalの変更が反映されない)\n\n", deep);
}

int main(void) {
    printf("=== Shallow Copy と Deep Copy の違いデモ ===\n\n");

    demonstrate_array_shallow_deep();

    return 0;
}
