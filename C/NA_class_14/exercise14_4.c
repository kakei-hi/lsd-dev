//
// 国名 - 首都名マッチング
//

#include    <stdio.h>
#include    <string.h>

int main()
{
    // データセット country[データ番号][データ種別][データ]
    char    country[5][2][50];

    // 入力国名
    char    target[50];
    int     i;

    // データ代入
    // データ種別 0:国名 1:首都名
    strcpy(country[0][0], "JAPAN");
    strcpy(country[0][1], "TOKYO");

    strcpy(country[1][0], "FRANCE");
    strcpy(country[1][1], "PARIS");
    
    strcpy(country[2][0], "UK");
    strcpy(country[2][1], "LONDON");
    
    strcpy(country[3][0], "EGYPT");
    strcpy(country[3][1], "CAIRO");
    
    strcpy(country[4][0], "CHILE");
    strcpy(country[4][1], "SANTIAGO");

    printf("\n\n入力されているデータ");
    printf("\n国名\t\t首都名");
    for ( i = 0; i < 5; i++)
    {
        printf("\n%s\t\t%s", country[i][0], country[i][1]);
    }

    printf("\n\n首都名を知りたい国の名前を入力して下さい\t");
    fscanf(stdin, "%s", target);

    //  入力された国名に一致するデータを探す
    i = 0;
    while ((strcmp(target, country[i][0])) != 0 && i < 5)
    {
        i ++;
    }
    if (i < 5)
    {
        printf("\n%sの首都は%sです", target, country[i][1]);
    }
    else
    {
        printf("\n%sという国名はデータに見当たりませんでした", target);
    }

    printf("\n");

    return 0;
    
}