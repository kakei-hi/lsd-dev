//
//  データベースへの入力および修正
//  source11_2
//
//  Created by hide on 06/07/13.
//  Copyright __MyCompanyName__ 2006. All rights reserved.
//

#include	<stdio.h>
#include	<string.h>
#define		DAT			30
#define		MAXCHAR		100
int main()
{
	char	country[DAT][2][MAXCHAR];
	void	initArray(char x[DAT][2][MAXCHAR]), inputArray(char x[DAT][2][MAXCHAR]);
	void	outputArray(char x[DAT][2][MAXCHAR]), correctArray(char x[DAT][2][MAXCHAR]);
	
	//	データの初期化
	initArray(country);
	
	//	データの入力
	inputArray(country);
	
	//	データの表示
	outputArray(country);
	
	//	データの修正
	correctArray(country);
	
	//	データの表示
	outputArray(country);

    return 0;

}


void initArray(char data[DAT][2][MAXCHAR])
{
	int		i, j;
	
	for ( i = 0; i < DAT; i ++ ){
		for ( j = 0; j < 2; j ++){
			strcpy(data[i][j],"Q");
		}
	}
	
}



void inputArray(char i_d[DAT][2][MAXCHAR])
{
	int		i;
	
	i = 0;
	do{
		printf("\n国名を入力してください。終了する場合は'Q'を入力してください\t");
		scanf("%s",i_d[i][0]);
		i ++;
	}while ( strcmp(i_d[i - 1][0],"Q") != 0 && i < DAT );
	
	for ( i = 0; i < DAT; i ++ ){
		if ( strcmp(i_d[i][0],"Q") != 0 ){
			printf("\n%sの首都名を入力してください\t",i_d[i][0]);
			scanf("%s",i_d[i][1]);		
		}
	}

}


void outputArray(char dat[DAT][2][MAXCHAR])
{
	int		i;
	
	for ( i = 0; i < DAT; i ++ ){
		if ( strcmp(dat[i][0],"Q") != 0 ){
			printf("\nデータ番号%d：国名%s　首都名%s",i,dat[i][0],dat[i][1]);
		}
	}
	printf("\n");
	
}


void correctArray(char data[DAT][2][100])
{
	int		num, ans;
	void	input_country(char *), input_capital(char *);
	void	outputArray(char	x[DAT][2][MAXCHAR]);
	
	printf("\n修正を行うデータのデータ番号を入力してください");
	printf("\nデータを追加する場合は未使用のデータ番号（%d未満）を指定して国名と首都名の両方を修正して下さい",DAT);
	printf("\nデータ修正を終了する場合は%d以上の数値を入力してください\t",DAT);
	scanf("%d",&num);
	while ( num >= 0 && num < DAT ){
		printf("\nデータ番号%d：国名%s　首都名%s",num,data[num][0],data[num][1]);
		printf("\n国名を修正する・・・・1");
		printf("\n首都名を修正する・・・2");
		printf("\n両方を修正する・・・・3");
		printf("\nデータを削除する場合は'1'を選択し、国名に'Q'を入力してください\n");
		scanf("%d",&ans);
		switch(ans){
			case 1:	input_country(data[num][0]);
					break;
			case 2:	input_capital(data[num][1]);
					break;
			case 3:	input_country(data[num][0]);
					printf("\n");
					input_capital(data[num][1]);
					break;
			default:printf("入力された値が不適切です");
					break;
		}
		outputArray(data);
		printf("\n修正を行うデータのデータ番号を入力してください");
		printf("\nデータ修正を終了する場合は%d以上の整数を入力してください",DAT);
		scanf("%d",&num);
	}
	
}


void input_country(char *country)
{
	char	now[100];
	
	strcpy(now,country);
	printf("国名を入力してください\n");
	scanf("%s",country);
	printf("%s -> %s\n",now,country);
	
}


void input_capital(char *capital)
{
	char	now[100];
	
	strcpy(now,capital);
	printf("首都名を入力してください\n");
	scanf("%s",capital);
	printf("%s -> %s\n",now,capital);
	
}

