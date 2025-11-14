/**
 * input_buffer_clear.c
 * 
 * scanfの二重入力問題を入力バッファのクリアにより回避するサンプルコード
 * 
 * 【問題点】
 * scanf関数で文字を入力した後、次のscanf関数が実行されない問題が発生する。
 * これは、最初のscanf実行時に入力した改行文字('\n')が入力バッファに残るためである。
 * 
 * 【解決方法】
 * scanf実行後に入力バッファに残った文字を全て読み捨てることで、
 * 次のscanf関数が正常に動作するようになる。
 */

#include <stdio.h>

int main(void) {
    char first_char;
    char second_char;
    int number;
    int c;  // 入力バッファクリア用の変数
    
    printf("=== scanf二重入力問題のデモンストレーション ===\n\n");
    
    // 例1: 文字入力後の文字入力
    printf("【例1: 文字入力後の文字入力】\n");
    printf("1文字目を入力してください: ");
    scanf("%c", &first_char);
    
    // 入力バッファのクリア
    // 改行文字('\n')またはEOFが来るまで1文字ずつ読み捨てる
    while ((c = getchar()) != '\n' && c != EOF);
    
    printf("2文字目を入力してください: ");
    scanf("%c", &second_char);
    
    // 入力バッファのクリア
    while ((c = getchar()) != '\n' && c != EOF);
    
    printf("入力結果: 1文字目='%c', 2文字目='%c'\n\n", first_char, second_char);
    
    // 例2: 文字入力後の数値入力
    printf("【例2: 文字入力後の数値入力】\n");
    printf("文字を入力してください: ");
    scanf("%c", &first_char);
    
    // 入力バッファのクリア
    while ((c = getchar()) != '\n' && c != EOF);
    
    printf("数値を入力してください: ");
    scanf("%d", &number);
    
    // 入力バッファのクリア
    while ((c = getchar()) != '\n' && c != EOF);
    
    printf("入力結果: 文字='%c', 数値=%d\n\n", first_char, number);
    
    // 例3: 数値入力後の文字入力
    printf("【例3: 数値入力後の文字入力】\n");
    printf("数値を入力してください: ");
    scanf("%d", &number);
    
    // 入力バッファのクリア
    while ((c = getchar()) != '\n' && c != EOF);
    
    printf("文字を入力してください: ");
    scanf("%c", &first_char);
    
    // 入力バッファのクリア
    while ((c = getchar()) != '\n' && c != EOF);
    
    printf("入力結果: 数値=%d, 文字='%c'\n\n", number, first_char);
    
    printf("=== プログラム終了 ===\n");
    
    return 0;
}
