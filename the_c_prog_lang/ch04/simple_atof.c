#include <stdio.h>
#include <stdbool.h>
#include <math.h>


#define MAX_STR_LEN 20
#define TOLERANCE 1.0e-6


// My initial version
double simple_atof_v1(char s[]) {
    int sign = (s[0] == '-') ? -1 : 1;
    int i = 0;

    if ((s[0] == '-') || (s[0] == '+')) {
        ++i;
    }

    bool is_fractional_part = false;
    double integral_part = 0.0;
    double fractional_part = 0.0;
    double fract_div = 1.0;
    while (s[i] != '\0') {
        if (s[i] != '.') {
            const int digit = s[i] - '0';
            if (is_fractional_part) {
                fract_div *= 10.0;
                fractional_part += (digit/fract_div);
            } else {
                integral_part = 10 * integral_part + digit;
            }
        } else {
            is_fractional_part = true;
        }
        ++i;
    }
    return sign * (integral_part + fractional_part);
}


// Inspired from the book
double simple_atof_v2(char s[]) {
    // Idea is the we process the input string from left to right for sign, integral part, decimal
    // point and finally the fractional part
    int i = 0;
    
    int sign = (s[0] == '-') ? -1 : 1;
    
    // Step 1: Parse sign
    if ((s[0] == '-') || (s[0] == '+')) {
        ++i;
    }

    // Step 2: Integral part
    double integral_part = 0.0;
    while ((s[i] != '\0') && (s[i] != '.')) {
        const int digit = s[i] - '0';
        integral_part = 10 * integral_part + digit;
        ++i;
    }

    // Step 3: Skip the decimal point
    if (s[i] == '.') {
        ++i;
    }
    
    // Step 4: Fractional part
    double fractional_part = 0.0;
    double fract_div = 1.0;
    while ((s[i] != '\0') && (s[i] != 'e') && (s[i] != 'E')) {
        const int digit = s[i] - '0';
        fract_div *= 10.0;
        fractional_part = 10 * fractional_part + digit;
        ++i;
    }

    // Step 5: Check if e or E exponent
    if ((s[i] == 'e') || (s[i] == 'E')) {
        ++i;
    }

    // Step 6: Check sign of exponent
    int exp_sign = (s[i] == '-') ? -1 : 1;
    // printf("exp sign = %d\n", exp_sign);
    
    // Step 8: Parse exponent sign
    if ((s[i] == '-') || (s[i] == '+')) {
        ++i;
    }
    
    // Step 9: Exponential part
    int exp = 0;
    while (s[i] != '\0') {
        const int digit = s[i] - '0';
        exp = 10 * exp + digit;
        ++i;
    }
    // printf("exp = %d\n", exp);

    double exponent_value = 1.0;
    for (int j = 0; j < exp; ++j) {
        exponent_value *= 10;
    }
    // printf("exp val = %f\n", exponent_value);
    if (exp_sign == -1) {
        exponent_value = 1.0/exponent_value;
    }
    // printf("final exp val = %f\n", exponent_value);
    
    return sign * ((integral_part + (fractional_part / fract_div)) * exponent_value);
}


typedef struct test_data {
    char s[MAX_STR_LEN];
    double expected;
    bool test_v1;
} test_data;


int main() {
    bool debug = false;
    
    printf("Running tests for simple_atof\n");

    test_data tests[] = {
        {"1.2", 1.2, true},
        {"-1.2", -1.2, true},
        {"0.02", 0.02, true},
        {"-0.02", -0.02, true},
        {"200.0", 200.0, true},
        {"-200.0", -200.0, true},
        {"42.12", 42.12, true},
        {"-42.12", -42.12, true},
        {"+12.345", 12.345, true},
        {"-12.345", -12.345, true},
        {"1.23e1", 12.3, false},
        {"-1.23e1", -12.3, false},
        {"12.3e-1", 1.23, false},
        {"-12.3e-1", -1.23, false},
        {"1.23e01", 12.3, false},
        {"-1.23e01", -12.3, false},
        {"12.3e-01", 1.23, false},
        {"-12.3e-01", -1.23, false},
        {"+1.234e02", 123.4, false},
        {"-1.234e02", -123.4, false}
    };

    unsigned int num_failed = 0;
    for (int i = 0; i < sizeof(tests)/sizeof(test_data); ++i) {
        if (tests[i].test_v1) {
            const double result1 = simple_atof_v1(tests[i].s);
            if (debug) {
                printf("s = %s, expected = %f, result1 = %f\n",
                       tests[i].s,
                       tests[i].expected,
                       result1);
            }
            if (fabs(result1 - tests[i].expected) > TOLERANCE) {
                printf("s = %s, expected = %f, result1 = %f\n",
                       tests[i].s,
                       tests[i].expected,
                       result1);
                ++num_failed;
            }
        }
        
        const double result2 = simple_atof_v2(tests[i].s);

        if (debug) {
            printf("s = %s, expected = %f, result2 = %f\n",
                   tests[i].s,
                   tests[i].expected,
                   result2);
        }
        if (fabs(result2 - tests[i].expected) > TOLERANCE) {
            printf("s = %s, expected = %f, result2 = %f\n",
                   tests[i].s,
                   tests[i].expected,
                   result2);
            ++num_failed;
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
