#include <stdbool.h>
#include <stdio.h>


void expand(char input[], char output[]) {}


typedef struct test_data {
    char input[20];
    char output[20];
} test_data;


bool compare_string(char s1[], char s2[]) {
    int i = 0;
    while(true) {
        if (s1[i] != s2[i]) {
            return false;
        }
        if (s1[i] == '\0') {
            break;
        }
        ++i;
    }
    return true;
}


int main() {
    bool debug = false;
    
    printf("Running tests for expand\n");

    test_data arr [] = {
        {"a-z", "abcdefghijklmnopqrstuvwxyz"},
        {"0-9", "0123456789"},
        {"a-z0-9", "abcdefghijklmnopqrstuvwxyz0123456789"},
        {"", ""},
        {"a", "a"},
        {"aa", "aa"},
        {"abcdef", "abcdef"},
        {"ab-d", "abcd"},
        {"-a-d", "-abcd"},
        {"a-d-", "abcd-"},
        {"-a-d-", "-abcd-"},
        {"-a-d0-3", "-abcd0123"},
        {"-c-g2-6", "-cdefg23456"},
        {"c-g2-6-", "cdefg23456-"},
        {"-c-g2-6-", "-cdefg23456-"},
        {"-", "-"},
        {"--", "--"},
        {"---", "---"},
        {"-a", "-a"},
        {"a-", "a-"},
        {"-a-", "-a-"},
        {"-ab", "-ab"},
        {"ab-", "ab-"},
        {"-ab-", "-ab-"},
        {"-*#$", "-*#$"},
        {"*&-()", "*&-()"},
        {"!-!", "!-!"},
        {"a-a", "a"},
        {"2-2", "2"},
        {"a-b-c", "abc"},
        {"a-d-g", "abcdefg"},
        {"0-3-5", "012345"},
        {"a-d-g0-3-5", "abcdefg012345"},
        {"d-a", "d-a"},
        {"z-a", "z-a"},
        {"9-0", "9-0"},
        {"g-c7-2", "g-c7-2"},
        {"a-0", "a-0"},
        {"0-a", "0-a"},
        {"a - z", "a - z"},
        {"a- z", "a- z"},
        {"a -z", "a -z"},
        {"0 - 9", "0 - 9"},
        {"0- 9", "0- 9"},
        {"0 -9", "0 -9"},
        {"a-d0 -9", "abcd0 -9"},
        {"0-5a -z", "012345a -z"},
        {"9-6-2", "9-6-2"},
        {"z-w-s", "z-w-s"}
    };

    unsigned int num_failed = 0;
    for (int i = 0; i < sizeof(arr)/sizeof(test_data); ++i) {
        if (debug) {
            printf("input = %s\n", arr[i].input);
        }
        
        reverse_string(arr[i].input);
        
        if (debug) {
            printf("output = %s, expected = %s\n", arr[i].input, arr[i].output);
        }
        if (!compare_string(arr[i].input, arr[i].output)) {
            printf("expected = %s, result = %s\n", arr[i].output, arr[i].input);
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
