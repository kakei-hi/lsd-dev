// 任意の文字列を逆転して表示

#include <stdio.h>
#include <string.h>

int main()
{
    int     i, n;
    char    str[100];

    printf("\n文字列を入力して下さい（ただし，英数半角文字で99文字以内）\t");
    fscanf(stdin, "%s", str);

    printf("入力された文字列は\'%s\'です．\n", str);

    printf("文字列を逆転すると\'");
    n = strlen(str);
    for ( i = (n - 1); i >= 0; i--)
    {
        printf("%c", str[i]);
    }
    printf("\'となります\n");

    return 0;

}