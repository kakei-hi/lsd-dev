#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INPUT_BUFFER_SIZE 100
#define MAX_INPUT_CHARACTERS (INPUT_BUFFER_SIZE - 1)

int main(void)
{
    char input[INPUT_BUFFER_SIZE] = {0};

    printf("文字列を入力してください（最大99文字）: ");
    if (scanf("%s", input) != 1)
    {
        printf("入力を読み取れませんでした。\n");
        return EXIT_FAILURE;
    }
    printf("入力した文字列: %s\n", input);

    // 逆順で出力するが input は変更しない
    size_t length = strlen(input);
    printf("逆転した文字列: ");
    for (size_t i = length; i > 0; --i)
    {
        putchar(input[i - 1]);
    }
    printf("\n");

    return EXIT_SUCCESS;
}
