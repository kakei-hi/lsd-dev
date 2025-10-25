// continueとbreak

#include <stdio.h>

int main()
{
    int     i;

    for (i = 0; i < 5; i++){
        if (i == 3){
            continue;
        }
        printf("\n%d回目", i + 1);
    }
    
    for (i = 0; i < 5; i++){
        if (i == 3){
            break;
        }
        printf("\n%d回目", i + 1);
    }
    printf("\n");

}