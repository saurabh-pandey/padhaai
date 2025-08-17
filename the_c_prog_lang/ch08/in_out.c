#include <unistd.h>

#define BUFSIZE 100


int main() {
    char buf[BUFSIZE];
    ssize_t n = 0;
    
    while((n = read(0, buf, sizeof buf)) > 0) {
        write(1, buf, n);
    }

    return 0;
}
