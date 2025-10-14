#include <stdio.h>

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int *month, int *pday);

int main()
{
    int d = day_of_year(2019, 5, 20);
    printf("days: %d\n", d);
    int pmonth, pday;
    month_day(2018, 20, &pmonth, &pday);
    printf("month_day conversion month: %d\nday:%d\n", pmonth, pday);
}

int day_of_year(int year, int month, int day)
{
    // What if month, or day are out of bounds?
    if (month < 1 || month > 12 || year < 0)
        return -1;
    int i, leap;
    leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
    char *p = *(daytab + leap);
    if (day < 1 || day > *(p + month))
        return -1;
    for (i = 1; i < month; i++)
        day += *(p + i);
    return day;
}

void month_day(int year, int yearday, int *pmonth, int *pday)
{
    int i, leap;
    leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
    if (year < 0) {
       *pmonth = -1;
        *pday = -1;
        return;
    }
    int max_days = 0;
    char *p = *(daytab + leap);
    for (int j = 1; j < 13; j++) {
        max_days += *(p + j);
    }
    if (yearday < 1 || yearday > max_days) {
        *pmonth = -1;
        *pday = -1;
        return;
    }
    char *curr_days = *(daytab + leap) + 1; 
    for (i = 1; yearday > *curr_days; curr_days++, i++)
        yearday -= *(curr_days + i);
    *pmonth = i;
    *pday = yearday;
}
