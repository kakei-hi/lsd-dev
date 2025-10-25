#include <stdio.h>

int main() {
    int hour, minute, second;

    printf("Enter time (hh mm ss): ");
    scanf("%d %d %d", &hour, &minute, &second);

    if (hour < 0 || hour > 23 || minute < 0 || minute > 59 || second < 0 || second > 59) {
        printf("Invalid time input.\n");
        return 1;
    }

    printf("Time is %02d:%02d:%02d\n", hour, minute, second);

    return 0;
}
