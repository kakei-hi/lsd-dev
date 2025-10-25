/*
 *
 *	外貨換算
 *
 */

#include <stdio.h>

int main () 
{
	float	yen, usd, euro;				//	円，米ドル，ユーロ
	float	rateD, rateE;				//	対米ドルレート，対ユーロレート
	
	//		exchange（円，対米ドルレート，対ユーロレート，米ドル，ユーロ）
	void	exchange(float, float, float, float *, float *);
	
	printf("\n為替レートを入力してください");
	printf("\n対米ドル\t");
	fscanf(stdin, "%f", &rateD);
	printf("\n対ユーロ\t");
	fscanf(stdin, "%f", &rateE);

	printf("\n換算金額を入力してください\t");
	fscanf(stdin, "%f", &yen);
	
	exchange(yen, rateD, rateE, &usd, &euro);
	
	printf("\n%.2f円は%.2f米ドル，%.2fユーロです", yen, usd, euro);

    printf("\n");
	
    return 0;
	
}


//
//	外貨換算
//	与えられた金額（円）および為替レート（対米ドル，対ユール）から
//	外貨金額（米ドル，ユーロ）を計算する
//

void exchange(float y, float y2d, float y2e, float *d, float *e)
{
	*d = y / y2d;
	*e = y / y2e;
	
	return;
	
}
