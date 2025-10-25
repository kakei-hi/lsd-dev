// 今月のカレンダーを表示するプログラム
#include <stdio.h>
#include <time.h>

int main() {
    time_t timer;
    struct tm *local;
    int year, month, day;
    int i, j;
    int days_in_month[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    char *week_days[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

    timer = time(NULL);
    local = localtime(&timer);

    year = local->tm_year + 1900;
    month = local->tm_mon + 1;
    day = local->tm_mday;

    // うるう年の判定
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        days_in_month[2] = 29;
    }

    // 今月の1日の曜日を計算
    local->tm_mday = 1;
    mktime(local); // tm_wdayを更新
    int first_day_of_week = local->tm_wday;

    printf("\n        %d年%d月\n", year, month);
    for (i = 0; i < 7; i++) {
        printf("%s ", week_days[i]);
    }
    printf("\n");

    // 1日までの空白を埋める
    for (i = 0; i < first_day_of_week; i++) {
        printf("    ");
    }

    // 日付を表示
    for (j = 1; j <= days_in_month[month]; j++) {
        printf("%3d ", j);
        if ((first_day_of_week + j) % 7 == 0) {
            printf("\n");
        }
    }
    printf("\n\n");

    return 0;
}
