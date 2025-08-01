#include <stdio.h>
#include <stdarg.h>


void minprintf(char *fmt, ...) {
    va_list ap;
    char *p;
    int i_val;
    double d_val;
    char *s_val;
    
    va_start(ap, fmt);
    for (p = fmt; *p != '\0'; ++p) {
        if (*p != '%') {
            putchar(*p);
        } else {
            ++p;
            switch (*p)
            {
                case 'd':
                {
                    i_val = va_arg(ap, int);
                    printf("%d", i_val);
                    break;
                }
                case 'f':
                {
                    d_val = va_arg(ap, double);
                    printf("%f", d_val);
                    break;
                }
                case 's':
                {
                    for (s_val = va_arg(ap, char *); *s_val != '\0'; ++s_val) {
                        putchar(*s_val);
                    }
                    break;
                }
                default:
                {
                    putchar(*p);
                    break;
                }
            }
        }
    }
    va_end(ap);
}


int main() {
    printf("Running tests for minprintf\n");

    minprintf("input int %d input double %f input str %s\n", 42, 3.14, "Hello, World");
    minprintf("Another test with negative int %d\n", -10);
    minprintf("Another test with negative double %f\n", -2.71);
    minprintf("Another test with empty string \"%s\"\n", "");
    minprintf("%s%d%f\n", "ABC", 123, 3.21);

    printf("Done\n");
    
    return 0;
}
