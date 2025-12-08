//
//	ソート
//	配列とポインタ
//

#include	<stdio.h>
#include	<stdlib.h>		//	rand(), srand(), malloc(), free()
#include	<time.h>		//	time()

#define		ARRAY_SIZE	10	//	整数列の要素数
							// #define 文字列X  (定数または式)
							// コード中の文字列Xを定数または式に置換する

int main()
{
	int		i, mth, ss[ARRAY_SIZE];		//	ss[ARRAY_SIZE]:整数列を格納する配列
	void	printResult(int *);	//	配列の内容をモニタに表示する関数
								//	配列のポインタを受け渡す
	void	mySort(int, int *);	//	整数列を指定された方法で並び替える関数
								//	並び替え方法と配列のポインタを受け渡す

	//	整数列を配列に格納
	srand(time(NULL));		//	乱数のシードを設定
	for ( i = 0; i < ARRAY_SIZE; i ++ ){
		ss[i] = rand() % 30;	// 0以上30未満の整数を代入
	}

	//	配列の内容を出力
	printResult(ss);

	printf("\nソート方法を入力してください");
	printf("\n昇順・・・1　　降順・・・2　　終了・・・99\t");
	fscanf(stdin, "%d", &mth);
	while ( mth != 99 ){
		if ( mth == 1 || mth == 2 ){
			mySort(mth, ss);
			printResult(ss);
		}
		else {
			printf("\n入力された値が適切ではありません");
		}
		printf("\nソート方法を入力してください");
		printf("\n昇順・・・1　　降順・・・2　　終了・・・99\t");
		fscanf(stdin, "%d",&mth);
	}

	printf("\nプログラムを終了します\n");

    return 0;
}

/************************************************************

	配列の内容を出力

************************************************************/

 //void printResult(int *dat)
void printResult(int dat[])
{
	int		i;

	printf("(");
	for ( i = 0; i < ARRAY_SIZE; i ++ ){
		if ( i != (ARRAY_SIZE - 1) ){
			printf("%d,",*(dat + i));
		}
		else {
			printf("%d)",*(dat + i));
		}
	}

}


/************************************************************

	整数列の並び替え
		与えられた整数列のコピーを作成
		コピーされた整数列で大小を比較
		結果を与えられたポインタが指示する配列に返す

************************************************************/

void mySort(int method, int dat[])
{
	int		i, j, k, m_num, l_num, e_num, ofs, cpy[ARRAY_SIZE];

	//	整数列のコピーの作成
	for ( i = 0; i < ARRAY_SIZE; i ++ ){
		cpy[i] = dat[i];
	}

	//	着目した要素の値が与えられた整数列の中で
	//	何番目に大きいのか（小さいのか）
	//	等しい整数は幾つあるかを
	//	カウントし、その値を適切な位置に代入する
	for ( i = 0; i < ARRAY_SIZE; i ++ ){
		m_num = l_num = e_num = 0;
		for ( j = 0; j < ARRAY_SIZE; j ++ ){
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
		if ( method == 1 ){
			ofs = l_num;
		}
		else {
			ofs = m_num;
		}
		dat[ofs] = cpy[i];
		for ( k = 0; k < e_num; k ++ ){
			dat[k + ofs] = cpy[i];
		}
	}

}
