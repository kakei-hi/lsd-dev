//
//  Bingo
//  連続する正整数列から任意の個数の数値を
//  重複しないように抽出する
//

#include    <stdio.h>
#include    <stdlib.h>
#include    <time.h>

int main()
{
    int     m, n, p;
    int     i, length;
    int     *array;
    void    shuffle(int *, int);

    printf("\n正整数列の範囲[m, n]を指定してください\t");
    fscanf(stdin, "%d, %d", &m, &n);

    // 配列領域の自動確保
    length = n - m + 1; // 要素数
    array = (int*)malloc(sizeof(int) * length);

    //  連続する正整数で配列を初期化
    for ( i = 0; i < length; i++){
        array[i] = i + m;
    }

    //  配列をシャッフルする
    shuffle(array, length);

    printf("抽出する数字の個数pを指定して下さい\t");
    fscanf(stdin, "%d", &p);

	printf("\n区間[%d, %d]の連続する正整数列から%d個の数値を重複なく選択する\n", m, n, p);
	printf("(");
	for ( i = 0; i < p; i ++ ){
        if ( i != p - 1){
            printf("%d, ",array[i]);
        }
        else {
            printf("%d",array[i]);
        }
	}
	printf(")\n");
    
    free(array);

    return 0;

}

//  Fisher-Yates shuffleアルゴリズム
void shuffle(int *box, int size)
{
    int     i, j, tmp;

    // 乱数のseedを設定
    srand((unsigned)time(NULL));

    for ( i = size - 1; i  > 0; i-- ){
        j = rand() % (i + 1);
        tmp = box[j];
        box[j] = box[i];
        box[i] = tmp;
    }

    return;
}

