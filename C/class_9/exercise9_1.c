/**
 * exercise9_1.c
 * 
 * サイコロを振って1の目が10000回出るまでに
 * 他の目がそれぞれ何回出るかを調べるプログラム
 * 
 * 【処理の流れ】
 * 1. 乱数生成器を初期化
 * 2. サイコロの出目カウンター配列を初期化
 * 3. 1の目が10000回出るまでサイコロを振り続ける
 * 4. 各目の出現回数を表示
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 定数定義（Magic Numberを避ける）
#define DICE_FACES 6           // サイコロの面の数
#define TARGET_COUNT 10000     // 1の目の目標出現回数
#define DICE_ONE_INDEX 0       // 配列内で1の目を表すインデックス

int main(void)
{
    int i;                     // ループカウンター
    int dice[DICE_FACES];      // dice[x]: (x+1)の目の出た回数のカウンター
    int roll_result;           // サイコロを振った結果（0〜5）
    
    // 乱数生成器の初期化（現在時刻をシード値として使用）
    // time() が失敗した場合は固定シードにフォールバック
    time_t current_time = time(NULL);
    if (current_time == (time_t)-1) {
        printf("警告: time() の取得に失敗したため、固定シードで初期化します。\n");
        srand(12345);  // 固定シード（再現性のため）
    } else {
        srand((unsigned)current_time);
    }
    
    // すべての目のカウンターを0で初期化
    for (i = 0; i < DICE_FACES; i++) {
        dice[i] = 0;
    }
    
    // 1の目がTARGET_COUNT回出るまでサイコロを振り続ける
    while (dice[DICE_ONE_INDEX] < TARGET_COUNT) {
        // サイコロを振る（0〜5の乱数を生成）
        roll_result = rand() % DICE_FACES;
        
        // 出た目のカウンターを増やす
        dice[roll_result]++;
    }
    
    // 結果の表示
    printf("\n=== サイコロの出目統計結果 ===\n");
    printf("1の目が%d回出るまでの各目の出現回数:\n\n", TARGET_COUNT);
    
    for (i = 0; i < DICE_FACES; i++) {
        printf("%dの目: %6d回\n", i + 1, dice[i]);
    }
    
    printf("\n");
    
    return 0;
}
