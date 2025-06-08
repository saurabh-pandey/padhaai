#include <stdio.h>
#include <stdbool.h>


static char daytable[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};


int is_leap_year(int year) {
    if (year % 4 != 0) {
        return 0;
    }
    if ((year % 100 == 0) && (year % 400 != 0)) {
        return 0;
    }
    return 1;
}


int day_of_year(int year, int month, int day) {
    if (month < 1 || month > 12) {
        printf("ERROR: Month is %d but should be between [1, 12]\n", month);
        return 0;
    }

    if (day < 1 || day > 31) {
        printf("ERROR: Day is %d but should always be between [1, 31]\n", day);
        return 0;
    }
    
    const int is_leap_index = is_leap_year(year);

    int num_days = 0;
    for (int i = 1; i < month; ++i) {
        num_days += daytable[is_leap_index][i];
    }
    num_days += day;
    return num_days;
}

void month_day(int year, int yearday, int *pmonth, int *pday) {
    int month = 1;
    const int is_leap_index = is_leap_year(year);
    while (yearday > daytable[is_leap_index][month])
    {
        yearday -= daytable[is_leap_index][month];
        ++month;
    }
    *pmonth = month;
    *pday = yearday;
}

typedef struct test_data {
    int year;
    int month;
    int day;
    int day_of_year;
} test_data;


int main() {
    bool debug = false;
    
    printf("Running tests for day_month_year\n");

    test_data tests[] = {
        {2025, 1, 1, 1},
        {2025, 1, 31, 31},
        {2025, 2, 15, 46},
        {2025, 6, 19, 170},
        {2025, 10, 6, 279},
        {2025, 12, 25, 359},
        {2025, 12, 31, 365},
        {2024, 1, 1, 1},
        {2024, 1, 31, 31},
        {2024, 2, 15, 46},
        {2024, 6, 19, 171},
        {2024, 10, 6, 280},
        {2024, 12, 25, 360},
        {2024, 12, 31, 366},
        {2000, 1, 1, 1},
        {2000, 1, 31, 31},
        {2000, 2, 15, 46},
        {2000, 6, 19, 171},
        {2000, 10, 6, 280},
        {2000, 12, 25, 360},
        {2000, 12, 31, 366},
        {1900, 1, 1, 1},
        {1900, 1, 31, 31},
        {1900, 2, 15, 46},
        {1900, 6, 19, 170},
        {1900, 10, 6, 279},
        {1900, 12, 25, 359},
        {1900, 12, 31, 365}
    };

    unsigned int num_failed = 0;
    for (int i = 0; i < sizeof(tests)/sizeof(test_data); ++i) {
        const int day_year = day_of_year(tests[i].year, tests[i].month, tests[i].day);
        
        if (debug) {
            printf("\nyear = %d, month = %d, day = %d, day_of_year = %d\n",
                   tests[i].year, tests[i].month, tests[i].day, day_year);
        }
        
        if (day_year != tests[i].day_of_year) {
            ++num_failed;
        }

        int month = 0;
        int day = 0;
        month_day(tests[i].year, day_year, &month, &day);
        if ((month != tests[i].month) || (day != tests[i].day)) {
            ++num_failed;
        }

        if (debug) {
            printf("year = %d, day_of_year = %d, month = %d, day = %d\n",
                   tests[i].year, day_year, month, day);
        }
    }
    if (num_failed > 0) {
        printf("%d test failed\n", num_failed);
    } else {
        printf("All tests passed\n");
    }
    printf("Done\n");

    return 0;
}
