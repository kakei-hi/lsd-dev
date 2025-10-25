//
// 浅いコピー 深いコピー
//

#include <stdio.h>

int main()
{
    char     array0[] = {'t', 'a', 'k', 'e', '\0'};
  
    char    *shallow;
    char    deep[5];

    //  浅いコピー
    shallow = array0;

    //  深いコピー
    for (int i = 0; i < 5; i ++){
        deep[i] = array0[i];
    }

    printf("変更前\n");
    printf("元の配列の中身: %s\n", array0);
    printf("*shallowの中身: %s\n", shallow);
    printf("deepの中身: %s\n", deep);

    array0[0] = 'c';
    printf("変更後\n");
    printf("元の配列の中身: %s\n", array0);
    printf("*shallowの中身: %s\n", shallow);
    printf("deepの中身: %s\n", deep);

    return 0;

}