#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_INPUT_SIZE 100


void getinput(char *inp) {
    char c;
    int i = 0;
    while (i < (MAX_INPUT_SIZE - 1)) {
        c = getchar();
        printf("c = %c\n", c);
        if (c == EOF) {
            break;
        }
        if (c == '\n') {
            break;
        }
        inp[i++] = c;
    }
    inp[i] = '\0';
    printf("Input = %s\n", inp);
    return;
}


void minscanf(char *fmt, ...) {
    char input[MAX_INPUT_SIZE];
    getinput(input);
    
    va_list ap;
    // char c;
    char *fmt_p;
    char *inp_p = input;
    int *i_val;
    float *d_val;
    char *s_val;
    
    va_start(ap, fmt);
    for (fmt_p = fmt; *fmt_p != '\0'; ++fmt_p) {
        printf("fmt_p = %c\n", *fmt_p);
        if (*fmt_p != '%') {
            while(*inp_p != '\0') {
                printf("  inp_p = %c\n", *inp_p);
                if (isspace(*inp_p)) {
                    ++inp_p;
                    continue;
                }
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
            ++fmt_p;
            switch (*fmt_p)
            {
                case 'd':
                {
                    printf("Case d\n");
                    i_val = va_arg(ap, int*);
                    // printf("%d", i_val);
                    // scanf("%d", i_val);
                    int num = 0;
                    while (1) {
                        char c = *inp_p;
                        printf("  c = %c\n", c);
                        if (!isdigit(c)) {
                            break;
                        }
                        // printf("  c = %c\n", c);
                        num = (c - '0') + 10 * num;
                        ++inp_p;
                        // printf("  num = %d\n", num);
                    }
                    printf("  num = %d\n", num);
                    *i_val = num;
                    break;
                }
                case 'f':
                {
                    printf("Case f\n");
                    d_val = va_arg(ap, float*);
                    // printf("%f", d_val);
                    // scanf("%f", d_val);
                    char str[25];
                    int i = 0;
                    while (1) {
                        char c = *inp_p;
                        ++inp_p;
                        printf("  c = %c\n", c);
                        if (c != '.' && !isdigit(c)) {
                            break;
                        }
                        // printf("  c = %c\n", c);
                        str[i++] = c;
                        // printf("  num = %d\n", num);
                    }
                    str[i] = '\0';
                    *d_val = atof(str);
                    break;
                }
                case 's':
                {
                    printf("Case s\n");
                    // for (s_val = va_arg(ap, char *); *s_val != '\0'; ++s_val) {
                    //     putchar(*s_val);
                    // }
                    s_val = va_arg(ap, char*);
                    int i = 0;
                    while (*inp_p != '\0') {
                        char c = *inp_p;
                        ++inp_p;
                        printf("  c = %c\n", c);
                        if (isspace(c)) {
                            break;
                        }
                        s_val[i++] = c;
                        // printf("  num = %d\n", num);
                    }
                    s_val[i] = '\0';
                    // scanf("%s", s_val);
                    break;
                }
                default:
                {
                    // putchar(*p);
                    break;
                }
            }
        }
    }
    va_end(ap);
}


int main() {
    printf("Running tests for minscanf\n");

    int num = 0;
    printf("Enter an int: ");
    minscanf("%d", &num);
    printf("int = %d\n", num);

    // float real = 0;
    // printf("Enter a float: ");
    // minscanf("%f", &real);
    // printf("float = %f\n", real);

    // char str[20];
    // printf("Enter a str: ");
    // minscanf("%s", str);
    // printf("Str = %s\n", str);

    // int num = 0;
    // float real = 0.0;
    // printf("Enter an int(i) and a float(f) like i, f: ");
    // // scanf("%d, %f", &num, &real);
    // minscanf("%d,%f", &num, &real);
    // printf("Num = %d, real = %f\n", num, real);

    // num = 0;
    // str[0] = '\0';
    // minscanf("%d, %s", &num, str);
    // printf("Num = %d, str = %s\n", num, str);

    // real = 0;
    // str[0] = '\0';
    // minscanf("%f, %s", &real, str);
    // printf("Real = %f, str = %s\n", real, str);

    printf("Done\n");
    
    return 0;
}
