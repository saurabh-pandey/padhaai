#include <stdio.h>

void try_int(void) {
    int num = 0;

    printf("Enter an int: ");
    scanf("%d", &num);
    printf("int entered is = %d\n", num);
}

void try_double(void) {
    double num = 0;

    printf("Enter a double: ");
    scanf("%lf", &num);
    printf("double entered is = %f\n", num);
}

void try_string(void) {
    char str[20];

    printf("Enter a string: ");
    scanf("%s", str);
    printf("String entered is = %s\n", str);
}

void test_int_tuples(void) {
    int num1 = 0;
    int num2 = 0;
    int num3 = 0;
    printf("Enter three numbers like (n1, n2, n3): ");

    //NOTE: The space before '(' in below scanf is to ignore any newline character in the buffer!!
    scanf(" (%d, %d, %d)", &num1, &num2, &num3);
    printf("Three numbers are (%d, %d, %d)\n", num1, num2, num3);
}

void test_date_fmt1(void) {
    int date = 0;
    char month[20];
    int year = 0;

    printf("Enter date in dd-month_name_yy format (e.g. 02-March-1978): ");
    // scanf below won't work as string width is going to be the size of month (minus one for null 
    // char). Suppose I enter 18-March-2024 then the month array will be "March-2024" and year will
    // be 0.
    // scanf("%d-%s-%d", &date, month, &year);
    scanf("%d-%19[^-]-%d", &date, month, &year);
    printf("Entered date is %d-%s-%d\n", date, month, year);
}

void test_date_fmt2(void) {
    int date = 0;
    int month = 0;
    int year = 0;

    printf("Enter date in dd/mm/yyyy format (e.g. 02/03/1978): ");
    scanf("%d/%d/%d", &date, &month, &year);
    printf("Entered date is %d/%d/%d\n", date, month, year);
}

int main() {
    printf("Running tests for try_scanf\n");

    try_int();
    try_double();
    try_string();

    test_int_tuples();

    test_date_fmt1();

    test_date_fmt2();

    printf("Done\n");
    
    return 0;
}
