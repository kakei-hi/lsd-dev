// switch文　exercise

#include <stdio.h>

int main()
{
    int animal;

    printf("\nカラス:1 ニワトリ:2 ペンギン:3 コウモリ:4");
    printf("\nサル:5 ヒト:6 カモメ:7");

    printf("\nどの動物を選択しますか?\t");
    fscanf(stdin, "%d", &animal);

    printf("\n");
    switch (animal)
    {
    case 1:
        printf("カラスは");
        break;    
    case 2:
        printf("ニワトリは");
        break;    
    case 3:
        printf("ペンギンは");
        break;    
    case 4:
        printf("コウモリは");
        break;    
    case 5:
        printf("サルは");
        break;    
    case 6:
        printf("ヒトは");
        break;    
    case 7:
        printf("カモメは");
        break;    
    default:
        printf("1から7までの整数を入力してください");
        break;
    }

    switch (animal)
    {
    case 1:
    case 7:
        printf("空を飛べる");
    case 2:
    case 3:
        printf("鳥類です");
        break;
    case 4:
        printf("空を飛べる");
    case 5:
    case 6:
        printf("哺乳類です");
        break;
    }

    printf("\n");

}