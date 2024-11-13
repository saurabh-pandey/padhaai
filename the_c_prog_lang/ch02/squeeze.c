#include <stdio.h>
#include <stdbool.h>


// Remove all occurrence of c in input string
void squeeze(char input[], char c) {
    // Pathological input
    if (c == '\0') {
        return;
    }
    
    int j = 0;
    for (int i = 0; input[i] != '\0'; ++i) {
        if (input[i] != c) {
            input[j] = input[i];
            ++j;
        }
    }
    input[j] = '\0';
}

typedef struct test_data
{
    char input[12];
    char c;
} test_data;


int main() {
    bool debug = false;
    
    test_data arr[] = {
        {"abcde", 'c'},
        {"cacbcccd", 'c'},
        {"abcdef", 'g'},
        {"c", 'c'},
        {"", 'c'},
        {"cccc", 'c'},
        {"abdefc", 'c'},
        {"abcdef", '\0'}
    };

    int num_failed = 0;

    printf("Running tests for squeeze\n");

    for (int i = 0; i < sizeof(arr)/sizeof(test_data); ++i) {
        if (debug) {
            printf("Input = %s, char to be removed = %c", arr[i].input, arr[i].c);
        }
        squeeze(arr[i].input, arr[i].c);
        if (debug) {
            printf("Result = %s\n", arr[i].input);
        }
        if (arr[i].c != '\0') {
            for (int j = 0; arr[i].input[j] != '\0'; ++j) {
                if (arr[i].input[j] == arr[i].c) {
                    printf("Failed for test # %d\n", i);
                    ++num_failed;
                    break;
                }
            }
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