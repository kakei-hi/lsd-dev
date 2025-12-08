#include <stdio.h>
#include <string.h>

int main()
{
    char    c, str2[3][5] = {{"XYZ"}, {"12"}, {"*+?!"}};
    int     i, j;

    for ( i = 0; i < 3; i++)
    {
        // 文字列操作関数
        printf("\n\"%s\"の文字数は%d文字です", str2[i], strlen(str2[i]));
    }

    printf("\n");
    for ( i = 0; i < 3; i++)
    {
        printf("\n\"%s\"の文字数は", str2[i]);
        j = 0;
        // ループ処理
        while (str2[i][j] != '\0')
        {
            j ++;
        }
        printf("%d文字です", j);
    }

    printf("\n");

    return 0;

}
