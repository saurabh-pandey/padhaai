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

int getint(char **inp, char *out) {
    int i = 0;
    while (1) {
        char c = **inp;
        printf("  c = %c\n", c);
        
        if (i == 0) {
            if (isspace(c)) {
                ++(*inp);
                continue;
            }
            if (c == '-') {
                ++(*inp);
                out[i++] = c;
                continue;
            }
        }
        
        if (!isdigit(c)) {
            break;
        }
        ++(*inp);
        // printf("  c = %c\n", c);
        out[i++] = c;
        // printf("  num = %d\n", num);
    }
    out[i] = '\0';
    return i;
}

int getfloat(char **inp, char *out) {
    int i = 0;
    while (1) {
        char c = **inp;
        printf("  c = %c\n", c);
        
        if (i == 0) {
            if (isspace(c)) {
                ++(*inp);
                continue;
            }
            if (c == '-') {
                ++(*inp);
                out[i++] = c;
                continue;
            }
        }
        
        if (c != '.' && !isdigit(c)) {
            break;
        }
        ++(*inp);
        // printf("  c = %c\n", c);
        out[i++] = c;
        // printf("  num = %d\n", num);
    }
    out[i] = '\0';
    return i;
}

int getstr(char **inp, char *out) {
    int i = 0;
    while (**inp != '\0') {
        char c = **inp;
        printf("  c = %c\n", c);
        
        if (isspace(c)) {
            if (i == 0) {
                ++(*inp);
                continue;
            } else {
                // printf("  isspace true\n");
                break;
            }
        }
        ++(*inp);
        // printf("  c = %c\n", c);
        out[i++] = c;
    }
    out[i] = '\0';
    return i;
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
            if (isspace(*fmt_p)) {
                continue;
            }
            
            while(*inp_p != '\0') {
                printf("  inp_p = %c\n", *inp_p);
                printf("  fmt_p = %c\n", *fmt_p);
                // Ignore all spaces
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
                    char str[25];
                    getint(&inp_p, str);
                    *i_val = atoi(str);
                    break;
                }
                case 'f':
                {
                    printf("Case f\n");
                    d_val = va_arg(ap, float*);
                    char str[25];
                    getfloat(&inp_p, str);
                    *d_val = atof(str);
                    break;
                }
                case 's':
                {
                    printf("Case s\n");
                    s_val = va_arg(ap, char*);
                    getstr(&inp_p, s_val);
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

    float real = 0;
    printf("Enter a float: ");
    minscanf("%f", &real);
    printf("float = %f\n", real);

    char str[20];
    printf("Enter a str: ");
    minscanf("%s", str);
    printf("Str = %s\n", str);

    num = 0;
    real = 0.0;
    printf("Enter an int(i) and a float(f) like i, f: ");
    minscanf("%d, %f", &num, &real);
    printf("Num = %d, real = %f\n", num, real);

    num = 0;
    str[0] = '\0';
    printf("Enter an int(i) and a str(s) like i, s: ");
    minscanf("%d, %s", &num, str);
    printf("Num = %d, str = %s\n", num, str);

    real = 0;
    str[0] = '\0';
    printf("Enter an real(f) and a str(s) like f, s: ");
    minscanf("%f, %s", &real, str);
    printf("Real = %f, str = %s\n", real, str);

    printf("Done\n");
    
    return 0;
}
