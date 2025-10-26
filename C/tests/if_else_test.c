/*
 * if_else_test.c - `if_else_sample.c` の簡単なテストでござる
 * テストは標準出力に PASS/FAIL を出すでござる
 */

#include <stdio.h>
#include <string.h>

/* 外部関数のプロトタイプでござる */
int is_even(int n);
const char *grade_comment(int score);

/* 小さなアサート関数でござる (標準出力のみ) */
void assert_int_equal(const char *name, int got, int want) {
    if (got == want) {
        printf("PASS: %s -> got=%d\n", name, got);
    } else {
        printf("FAIL: %s -> got=%d want=%d\n", name, got, want);
    }
}

void assert_str_equal(const char *name, const char *got, const char *want) {
    if (got != NULL && want != NULL && strcmp(got, want) == 0) {
        printf("PASS: %s -> got=\"%s\"\n", name, got);
    } else {
        printf("FAIL: %s -> got=\"%s\" want=\"%s\"\n", name, got ? got : "(null)", want ? want : "(null)");
    }
}

int main(void) {
    printf("=== if_else tests ===\n");

    /* is_even のテストでござる */
    assert_int_equal("is_even(2)", is_even(2), 1);
    assert_int_equal("is_even(3)", is_even(3), 0);
    assert_int_equal("is_even(0)", is_even(0), 1);
    assert_int_equal("is_even(-4)", is_even(-4), 1);

    /* grade_comment のテストでござる */
    assert_str_equal("grade_comment(95)", grade_comment(95), "秀でござる");
    assert_str_equal("grade_comment(82)", grade_comment(82), "優でござる");
    assert_str_equal("grade_comment(73)", grade_comment(73), "良でござる");
    assert_str_equal("grade_comment(61)", grade_comment(61), "可でござる");
    assert_str_equal("grade_comment(50)", grade_comment(50), "不可でござる");
    assert_str_equal("grade_comment(-5)", grade_comment(-5), "無効な点数でござる");

    printf("=== tests finished ===\n");
    return 0;
}
