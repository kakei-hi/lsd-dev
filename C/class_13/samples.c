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
