#include <stdio.h>
#include <stdbool.h>


static char daytable[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};


int day_of_year(int year, int month, int day) {
    return 0;
}

void month_day(int year, int yearday, int *pmonth, int *pday) {

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
        {1989, 1, 1, 1}
    };

    unsigned int num_failed = 0;
    for (int i = 0; i < sizeof(tests)/sizeof(test_data); ++i) {
        const int day_year = day_of_year(tests[i].year, tests[i].month, tests[i].day);
        
        if (debug) {
            printf("year = %d, month = %d, day = %d, day_of_year = %d\n",
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
