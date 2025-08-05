#include <stdio.h>
#include <stdarg.h>


void minscanf(char *fmt, ...) {
    va_list ap;
    char *p;
    int *i_val;
    float *d_val;
    char *s_val;
    
    va_start(ap, fmt);
    for (p = fmt; *p != '\0'; ++p) {
        if (*p != '%') {
            // putchar(*p);
        } else {
            ++p;
            switch (*p)
            {
                case 'd':
                {
                    i_val = va_arg(ap, int*);
                    // printf("%d", i_val);
                    scanf("%d", i_val);
                    break;
                }
                case 'f':
                {
                    d_val = va_arg(ap, float*);
                    // printf("%f", d_val);
                    scanf("%f", d_val);
                    break;
                }
                case 's':
                {
                    // for (s_val = va_arg(ap, char *); *s_val != '\0'; ++s_val) {
                    //     putchar(*s_val);
                    // }
                    s_val = va_arg(ap, char*);
                    scanf("%s", s_val);
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

    printf("Done\n");
    
    return 0;
}
