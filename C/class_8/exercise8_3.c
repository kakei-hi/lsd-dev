/*
*	型変換と記憶クラス
*/

#include	<stdio.h>

int		XX;			//	外部変数であることをわかり易くするために大文字にしている
                    //	大文字にしなければ文法的に間違っているというわけではない

int main()
{
    int		xx, func1(void);
    
    printf("\nmain関数内のXXの値は\t\t%d", XX);		//【1】
    
    xx = 1;
    printf("\nmain関数内のxxの値は\t\t%d", xx);		//【2】
    
    func1();
    
    printf("\n");
    printf("\nmain関数内のXXの値は\t\t%d", XX);		//【8】
    printf("\nmain関数内のxxの値は\t\t%d", xx);		//【9】
    
    func1();
    
    return 0;
    
}


int func1()
{
    int			xx;
    static int	yy;
    
    printf("\n");
    printf("\nfunc1関数内のxxの値は\t%d", xx);			//【3】, 【10】
    xx = 100;
    printf("\nfunc1関数内のxxの値は\t%d", xx);			//【4】, 【11】
    
    printf("\nfunc1関数内のyyの値は\t%d", yy);			//【5】, 【12】
    yy += 10;		//	yy += 10; は yy = yy + 10; と同じ
    printf("\nfunc1関数内のyyの値は\t%d", yy);			//【6】, 【13】
    
    printf("\nfunc1関数内のXXの値は\t%d\n", XX);			//【7】, 【14】
    XX -= 100;		// XX -= 100; は XX = XX - 100; と同じ
    
    return 0;
    
}

