//
//		Bingo
//		連続する正整数列から任意の個数の数値を重複しないように抽出する
//

#include	<stdio.h>
#include	<stdlib.h>				//	srand(), rand()に必要
#include	<time.h>				//	time()に必要

#define		MAX_N	100				//	正整数列の要素数
#define		SL	99					//	選択する数値の個数

int main()
{
	int		box[MAX_N], i, num;
	void	init_array(int *), array_close(int, int *);

	srand((unsigned)time(NULL));		//	疑似乱数列のseed（種）を設定する
	
	init_array(box);					//	連続する正整数で配列を初期化する
	
	printf("要素数%d個の連続する正整数列から%d個の数値を重複なく選択する\n",MAX_N,SL);
	printf("(");
	for ( i = 0; i < SL; i ++ ){
		num = rand() % (MAX_N - i);
		if (i != SL - 1){
			printf("%d,",box[num]);			
		}
		else {
			printf("%d)",box[num]);						
		}
		array_close(num, box);
	}
	
	
    return 0;
}


/**********************************************
		連続する正整数で配列を初期化する
**********************************************/

void init_array(int array[])
{
	int		i;
	
	for ( i = 0; i < MAX_N; i ++ ){
		array[i] = i + 1;
	}
	
}


/**********************************************
	選択された要素から後ろの要素を前に詰める
***********************************************/

void array_close(int m, int dat[])
{
	int		i;
	
	for ( i = m; i < MAX_N - 1; i ++ ){
		dat[i] = dat[i + 1];
	}

}
