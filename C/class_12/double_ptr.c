//
//  ダブルポインタ
//

#include    <stdio.h>

// Magic Numberを定数化（初期値123）
#define INITIAL_VALUE 123

int main()
{
    // ダブルポインタの基本例：
    // value → intの実体
    // value_ptr → valueを指すポインタ
    // value_ptr_ptr → value_ptrを指すダブルポインタ
    int     value = INITIAL_VALUE;
    int     *value_ptr = &value;
    int     **value_ptr_ptr = &value_ptr;

    // 実体・ポインタ・ダブルポインタが同じ値を参照していることを確認
    printf("value = %d, *value_ptr = %d, **value_ptr_ptr = %d\n", value, *value_ptr, **value_ptr_ptr);

    // アドレスは%pを使い、void*へキャストして安全に表示
    printf("&value = %p, value_ptr = %p \n", (void*)&value, (void*)value_ptr);
    printf("&value_ptr = %p, value_ptr_ptr = %p \n", (void*)&value_ptr, (void*)value_ptr_ptr);

    return 0;

}
