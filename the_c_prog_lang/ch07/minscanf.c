#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <ctype.h>


void minscanf(char *fmt, ...) {
    va_list ap;
    char c;
    char *p;
    int *i_val;
    float *d_val;
    char *s_val;
    
    va_start(ap, fmt);
    for (p = fmt; *p != '\0'; ++p) {
        printf("p = %c, c = %c\n", *p, c);
        if (*p == '%') {
            ++p;
            switch (*p)
            {
                case 'd':
                {
                    printf("Case d\n");
                    i_val = va_arg(ap, int*);
                    // printf("%d", i_val);
                    // scanf("%d", i_val);
                    int num = 0;
                    while (1) {
                        c = getchar();
                        if (!isdigit(c)) {
                            break;
                        }
                        // printf("  c = %c\n", c);
                        num = (c - '0') + 10 * num;
                        // printf("  num = %d\n", num);
                    }
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
                        c = getchar();
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
                    while ((c = getchar()) != '\n') {
                        // printf("  c = %c\n", c);
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
    minscanf("%d", &num);
    printf("Num = %d\n", num);

    float real = 0;
    minscanf("%f", &real);
    printf("Real = %f\n", real);

    char str[20];
    minscanf("%s", str);
    printf("Str = %s\n", str);

    num = 0;
    real = 0;
    scanf("%d, %f", &num, &real);
    // minscanf("%d, %f", &num, &real);
    printf("Num = %d, real = %f\n", num, real);

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
