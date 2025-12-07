#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 64

/* 残っている入力を改行まで破棄する */
void clear_input_buffer(void)
{
    int ch = 0;
    while ((ch = getchar()) != '\n' && ch != EOF)
    {
        /* 入力を読み捨て */
    }
}

/* バッファ内容と末尾に改行が残っているかを表示する */
void print_buffer_info(const char *label, const char *buffer)
{
    size_t length = strlen(buffer);
    printf("%s: \"%s\" (長さ: %zu)", label, buffer, length);
    if (length > 0 && buffer[length - 1] == '\n')
    {
        printf(" -> 末尾に改行が残っています");
    }
    printf("\n");
}

int main(void)
{
    char buffer_scanf[BUFFER_SIZE];
    char buffer_fgets[BUFFER_SIZE];

    printf("空白を含む文章を入力してください。\n");
    printf("1) scanf(\"%%s\") は空白までしか読み取りません: ");

    if (scanf("%63s", buffer_scanf) != 1)
    {
        printf("scanf での読み取りに失敗しました。\n");
        return 1;
    }

    print_buffer_info("scanf の結果", buffer_scanf);

    /* scanf が標準入力に残した文字を次の fgets() が読み取る */
    if (fgets(buffer_fgets, BUFFER_SIZE, stdin) == NULL)
    {
        printf("残りの入力を fgets で読み取れませんでした。\n");
        return 1;
    }

    print_buffer_info("次の fgets() が受け取った残り", buffer_fgets);

    /* 次のデモ用に入力バッファを空にする */
    clear_input_buffer();

    printf("\n2) fgets() は空白を含む行全体を読み取れます。\n");
    printf("もう一度文章を入力してください: ");

    if (fgets(buffer_fgets, BUFFER_SIZE, stdin) == NULL)
    {
        printf("fgets で行を読み取れませんでした。\n");
        return 1;
    }

    /* 末尾の改行を削除 */
    size_t newline_index = strcspn(buffer_fgets, "\n");
    if (buffer_fgets[newline_index] == '\n')
    {
        buffer_fgets[newline_index] = '\0';
    }

    print_buffer_info("改行除去後の fgets の結果", buffer_fgets);

    printf("\n補足:\n");
    printf("- scanf(\"%%s\") は最初の空白で止まり、改行を含む残りは標準入力に残します。\n");
    printf("- fgets() は改行まで読み取るため、必要に応じて末尾の改行を自分で削除します。\n");

    return 0;
}
