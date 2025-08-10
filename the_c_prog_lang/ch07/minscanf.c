#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_INPUT_SIZE 100
#define MAX_STR_SIZE 20


void getinput(char *inp) {
    char c;
    int i = 0;
    while (i < (MAX_INPUT_SIZE - 1)) {
        c = getchar();

        // Input is assumed to end at EOF
        if (c == EOF) {
            break;
        }

        // Input is assumed to end at newline but ...
        if (c == '\n') {
            // if it is the first valid character I ignore it.
            // This allows to handle the case where a previous call to minscanf had the last
            // newline in the buffer and thus appears as the first char in the next minscanf call.
            if (i == 0) {
                continue;
            }
            break;
        }
        inp[i++] = c;
    }
    inp[i] = '\0';
    return;
}


int getint(char **inp, char *out) {
    int i = 0;
    while (1) {
        char c = **inp;
        if (i == 0) {
            // Ignore all the preceding spaces before a sign or digit
            if (isspace(c)) {
                ++(*inp);
                continue;
            }
            // Account for negative numbers
            if (c == '-') {
                ++(*inp);
                out[i++] = c;
                continue;
            }
        }
        // Not a digit break
        if (!isdigit(c)) {
            break;
        }
        ++(*inp);
        out[i++] = c;
    }
    out[i] = '\0';
    return i;
}


int getfloat(char **inp, char *out) {
    int i = 0;
    while (1) {
        char c = **inp;
        if (i == 0) {
            // Ignore all the preceding spaces before a sign or digit or a decimal point
            if (isspace(c)) {
                ++(*inp);
                continue;
            }
            // Account for -ve floats
            if (c == '-') {
                ++(*inp);
                out[i++] = c;
                continue;
            }
        }
        
        // Not a digit or a decimal point so break
        if (c != '.' && !isdigit(c)) {
            break;
        }
        ++(*inp);
        out[i++] = c;
    }
    out[i] = '\0';
    return i;
}


int getstr(char **inp, char *out) {
    int i = 0;
    while (**inp != '\0') {
        char c = **inp;
        if (isspace(c)) {
            // Ignore all the preceding spaces before a non space char arrives
            if (i == 0) {
                ++(*inp);
                continue;
            } else {
                break;
            }
        }
        ++(*inp);
        out[i++] = c;
    }
    out[i] = '\0';
    return i;
}


void minscanf(char *fmt, ...) {
    // First fetch the input as a string. Later I match it with the format string.
    char input[MAX_INPUT_SIZE];
    getinput(input);
    
    va_list ap;
    char *fmt_p;
    char *inp_p = input;
    int *i_val;
    float *d_val;
    char *s_val;
    
    va_start(ap, fmt);
    for (fmt_p = fmt; *fmt_p != '\0'; ++fmt_p) {
        // Non-format related characters are matched as it is
        if (*fmt_p != '%') {
            // Ignore all spaces in format string
            if (isspace(*fmt_p)) {
                continue;
            }
            
            // Now match the non-space format char with input char
            while(*inp_p != '\0') {
                // Ignore all spaces in input string
                if (isspace(*inp_p)) {
                    ++inp_p;
                    continue;
                }
                
                // Match format with input and warn in case of mismatch
                if (*fmt_p != *inp_p) {
                    printf("WARNING: Mismatch\n");
                    ++inp_p;
                    break;
                } else {
                    ++inp_p;
                    break;
                }
            }
        } else {
            // % should be followed by a valid input char
            ++fmt_p;
            switch (*fmt_p)
            {
                case 'd':
                {
                    i_val = va_arg(ap, int*);
                    char str[MAX_STR_SIZE];
                    getint(&inp_p, str);
                    *i_val = atoi(str);
                    break;
                }
                case 'f':
                {
                    d_val = va_arg(ap, float*);
                    char str[MAX_STR_SIZE];
                    getfloat(&inp_p, str);
                    *d_val = atof(str);
                    break;
                }
                case 's':
                {
                    s_val = va_arg(ap, char*);
                    getstr(&inp_p, s_val);
                    break;
                }
                default:
                {
                    printf("Format char %c is not yet supported\n", *fmt_p);
                    break;
                }
            }
        }
    }
    va_end(ap);
}


// All the test functions
void test_int(void) {
    int num = 0;
    
    printf("Enter an int: ");
    minscanf("%d", &num);
    printf("int = %d\n", num);
}


void test_float(void) {
    float real = 0;
    
    printf("Enter a float: ");
    minscanf("%f", &real);
    printf("float = %f\n", real);
}


void test_str(void) {
    char str[MAX_STR_SIZE];
    
    printf("Enter a str: ");
    minscanf("%s", str);
    printf("Str = %s\n", str);
}


void test_int_float_pair(void) {
    int num = 0;
    float real = 0.0;
    
    printf("Enter an int(i) and a float(f) like i, f: ");
    minscanf("%d, %f", &num, &real);
    printf("Num = %d, float = %f\n", num, real);
}


void test_int_str_pair(void) {
    int num = 0;
    char str[MAX_STR_SIZE];
    
    printf("Enter an int(i) and a str(s) like i, s: ");
    minscanf("%d, %s", &num, str);
    printf("Num = %d, str = %s\n", num, str);
}


void test_float_str_pair(void) {
    float real = 0.0;
    char str[MAX_STR_SIZE];
    
    printf("Enter an real(f) and a str(s) like f, s: ");
    minscanf("%f, %s", &real, str);
    printf("Float = %f, str = %s\n", real, str);
}


void test_three_nums(void) {
    int num1 = 0;
    int num2 = 0;
    int num3 = 0;
    
    printf("Enter three numbers like (n1, n2, n3): ");
    minscanf("(%d, %d, %d)", &num1, &num2, &num3);
    printf("Three numbers are (%d, %d, %d)\n", num1, num2, num3);
}


void test_date(void) {
    int date = 0;
    int month = 0;
    int year = 0;

    printf("Enter date in dd/mm/yyyy format (e.g. 02/03/1978): ");
    scanf("%d/%d/%d", &date, &month, &year);
    printf("Entered date is %d/%d/%d\n", date, month, year);
}


int main() {
    printf("Running tests for minscanf\n");

    test_int();
    test_float();
    test_str();

    test_int_float_pair();
    test_int_str_pair();
    test_float_str_pair();

    test_three_nums();
    test_date();

    printf("Done\n");
    
    return 0;
}
