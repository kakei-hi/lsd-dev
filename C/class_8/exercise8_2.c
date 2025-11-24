// 引数と戻り値

#include <stdio.h>

// 合計を求める
// 戻り値がfloat型であることを明示
// 引数は2つ，float型であることを明示
float sum(float a, float b)
{
    return(a + b);
}

// 平均を求める
float avg(float x, float y)
{
    return (x + y) / 2.0;
}

// 2数を比較して大きな数値を返す
float lrg(float x, float y)
{
    if (x > y){
        return x;
    }
    else{
        return y;
    }
    
}

int main()
{
    float mm, nn;
    float sum(float, float), avg(float, float), lrg(float, float);

    printf("\n2つの数値（float型）を空白区切りで入力して下さい（ex. 12.3 45.6）\t");

    // 入力安定化: 不正入力を検出し再入力を促すループ
    while (1) {
        // ユーザーには "12.3 45.6" のように入力してもらう
        if (scanf("%f %f", &mm, &nn) == 2) {
            break; // 正常に2つ読めたので終了
        } else {
            printf("入力が不正です。例: 12.3 45.6  の形式で再入力して下さい。\n");
        }
        // 入力バッファに残った文字列を破棄（重複読み取り回避）
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {
            /* 破棄 */
        }
        printf("> ");
    }

    printf("\n%.3fと%.3fの", mm, nn);

    printf("\n合計は%.3f", sum(mm,nn));
    printf("\n平均は%.3f", avg(mm,nn));
    printf("\n大きな数は%.3f", lrg(mm,nn));

    printf("\nです\n");

    return 0;
}
