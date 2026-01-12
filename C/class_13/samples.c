// samples
#include <stdio.h>

// 構造体の受け渡し（値渡し）
struct Student {
    char name[50];
    int id;
    float grade;
};

// 値渡し
void func1(struct Student s) {
    printf("%s %d %.2f\n", s.name, s.id, s.grade);
}

int main(void) {
    struct Student st = {"Alice", 1, 90.0f};
    func1(st); // copy is passed
    
    return 0;
}

// ポインタ渡し
void func2(struct Student *p, float g) {
    if (p) p->grade = g;
}

int main(void) {
    struct Student st = {"Bob", 279285, 75.0};
    func2(&st, 88.5); // st.grade changes
    
    return 0;
}

// ポインタ渡し（構造体配列）

struct Student 
{
    char name[50];
    int id;
    float grade;
};

void func3(struct Student *arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%s\n", arr[i].name);
    }
}
int main(void) {
    struct Student class[] = {
        {"Charlie", 1001, 85.0},
        {"David", 1002, 92.5},
        {"Eve", 1003, 78.0}
    };

    int size = sizeof(class) / sizeof(class[0]);
    func3(class, size); // array is passed
    
    return 0;

}

// ネスト構造体
struct Address {
    char prefecture[32];
    char city[32];
    char street[64];
};

struct Person {
    char name[64];
    int  age;
    struct Address addr;  // ← Address構造体をメンバとして持つ
};
int main(void) {
    struct Person p = {
        .name = "木曽 義仲",
        .addr = {
            .prefecture = "東京都",
            .city       = "港区",
            .street     = "南青山 4-2-8"
        },
        .age = 42
    };

    printf("%s lives in %s, %s, %s\n", p.name, p.addr.street, p.addr.city, p.addr.prefecture);
    
    return 0;
}
