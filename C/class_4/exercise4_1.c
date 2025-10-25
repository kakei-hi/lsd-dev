#include <stdio.h>

int main()
{
    char    ans;

    printf("\n紅茶とミルクではどちらがお好みですか？");
    printf("\n紅茶ならばT，ミルクならばMを入力してください");

    //  回答の入力
    fscanf(stdin, "%c", &ans);  // fscanf()では変数の前に'&'

    if (ans == 'T'){    // ''で囲み変数名ではなく文字であることを示す
        printf("\n紅茶が好きなんですね");
    }
    else if (ans == 'M')
    {
        printf("\nミルクが好きなんですね");        
    }
    else {
        printf("\n指定した文字を入力してください");
    }
    printf("\n");

    return 0;
    
}