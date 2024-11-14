#include <stdio.h>


// Find and return the index of any character in s2 that is present in s1. Otherwise return -1
int find_any(char s1[], char s2[]) {
    for(int i = 0; s1[i] != '\0'; ++i) {
        for (int j = 0; s2[j] != '\0'; ++j) {
            if (s1[i] == s2[j]) {
                return i;
            }
        }
    }
    return -1;
}


typedef struct test_data
{
    char s1[20];
    char s2[20];
    int result;
} test_data;


int main() {
    int debug = 0;
    test_data arr[] = {
        {"abc", "a", 0},
        {"abc", "b", 1},
        {"abc", "c", 2},
        {"abc", "d", -1},
        {"abcdef", "fghi", 5},
        {"abcdef", "ifhg", 5},
        {"abcdef", "ihfg", 5},
        {"abcdef", "ihgf", 5},
        {"abcdef", "jihg", -1},
        {"", "jihg", -1},
        {"abcdef", "", -1},
        {"", "", -1}
    };
    int num_failed = 0;

    printf("Running tests for any\n");

    for (int i = 0; i < sizeof(arr)/sizeof(test_data); ++i) {
        int result = find_any(arr[i].s1, arr[i].s2);
        int has_failed = (result != arr[i].result);
        if (has_failed) {
            ++num_failed;
        }
        if ((debug != 0) || has_failed) {
            printf("s1 = %s, s2 = %s, expected = %d, actual = %d\n",
                   arr[i].s1,
                   arr[i].s2,
                   arr[i].result,
                   result);
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