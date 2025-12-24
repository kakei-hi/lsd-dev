//
//	ソート
//	配列とポインタ
//

#include	<stdio.h>
#include	<stdlib.h>		//	rand(), srand(), malloc(), free()
#include	<time.h>		//	time()

// 追加: マジックナンバーの定数化
#define RANDOM_RANGE 30
#define MENU_ASC 1
#define MENU_DESC 2
#define MENU_EXIT 99

// 追加: プロトタイプ宣言（snake_case）
void print_array(const int *dat, int size);
void sort_array(int method, int *dat, int size);

int main()
{
	int		i, mth, *ss;		//	ss:整数列を格納する配列へのポインタ
    int	    array_size;	        //	整数列の要素数

    //  ソートする整数列の要素数を入力（入力チェック追加）
    printf("\nソートする整数列の要素数を入力してください\t");
    if (scanf("%d", &array_size) != 1 || array_size <= 0) {
        fprintf(stderr, "\n入力値が不正です（正の整数を指定してください）\n");
        return 1;
    }

    //  整数列を代入する配列の領域を確保（NULLチェック追加）
    ss = (int *)malloc(array_size * sizeof(int));
    if (ss == NULL) {
        fprintf(stderr, "\nメモリの確保に失敗しました\n");
        return 1;
    }

	//	整数列を配列に格納
	srand(time(NULL));		//	乱数のシードを設定
	for ( i = 0; i < array_size; i ++ ){
		ss[i] = rand() % RANDOM_RANGE;	// 0以上RANDOM_RANGE未満の整数を代入
	}

	//	配列の内容を出力（関数名変更）
	// printResult(ss, array_size);
	print_array(ss, array_size);

	printf("\nソート方法を入力してください");
	printf("\n昇順・・・%d　　降順・・・%d　　終了・・・%d\t", MENU_ASC, MENU_DESC, MENU_EXIT);
	// 入力チェック追加
	if (scanf("%d", &mth) != 1) {
		fprintf(stderr, "\n入力エラーが発生しました\n");
		free(ss);
		return 1;
	}
	while ( mth != MENU_EXIT ){
		if ( mth == MENU_ASC || mth == MENU_DESC ){
			// mySort(mth, ss, array_size);
			sort_array(mth, ss, array_size);
			// printResult(ss, array_size);
			print_array(ss, array_size);
		}
		else {
			printf("\n入力された値が適切ではありません");
		}
		printf("\nソート方法を入力してください");
		printf("\n昇順・・・%d　　降順・・・%d　　終了・・・%d\t", MENU_ASC, MENU_DESC, MENU_EXIT);
		// 入力チェック追加
		if (scanf("%d",&mth) != 1) {
			fprintf(stderr, "\n入力エラーが発生しました\n");
			break;
		}
	}

	printf("\nプログラムを終了します\n");

    //  確保したメモリ領域を開放する
    free(ss);

    return 0;
}

/************************************************************
	配列の内容を出力（snake_case & const安全化）
************************************************************/
void print_array(const int *dat, int size)
{
    printf("(");
    for ( int i = 0; i < size; i ++ ){
        if ( i != (size - 1) ){
            printf("%d,", dat[i]);
        }
        else {
            printf("%d)", dat[i]);
        }
    }
}

/************************************************************
	整数列の並び替え
************************************************************/
void sort_array(int method, int *dat, int size)
{
    // mySortのロジックそのまま
    int     i, j, k, m_num, l_num, e_num, ofs, *cpy;

    //  コピー先配列の領域を確保（NULLチェック追加）
    cpy = malloc(size * sizeof(*cpy));
    if (cpy == NULL) {
        fprintf(stderr, "\nメモリの確保に失敗しました\n");
        return;
    }

    //  整数列のコピーの作成
    for ( i = 0; i < size; i ++ ){
        cpy[i] = dat[i];
    }

	//	着目した要素の値が与えられた整数列の中で
	//	何番目に大きいのか（小さいのか）
	//	等しい整数は幾つあるかを
	//	カウントし、その値を適切な位置に代入する
	for ( i = 0; i < size; i ++ ){
		m_num = l_num = e_num = 0;
		for ( j = 0; j < size; j ++ ){
			if ( cpy[i] < cpy[j] ){
				m_num ++;
			}
			else if ( cpy[i] > cpy[j] ){
				l_num ++;
			}
			else {
				e_num ++;
			}
		}
		if ( method == MENU_ASC ){
			ofs = l_num;
		}
		else {
			ofs = m_num;
		}
		dat[ofs] = cpy[i];
		for ( k = 0; k < e_num; k ++ ){
			*(dat + (k + ofs)) = cpy[i];
		}
	}

    //  確保したメモリ領域を開放する
    free(cpy);
}
