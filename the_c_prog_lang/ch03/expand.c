#include <stdbool.h>
#include <stdio.h>

#define MAX_SIZE_INPUT 20
#define MAX_SIZE_OUTPUT 100


void expand(char input[], char output[]) {
    // Basic idea is to have a list of "Series" that we support expanding
    // For eg, a-z is abcd ... xyz
    // Start looping through input
    // If char is "-" and their are some chars to the left and right
    // Left char < right char
    // Left char and right char should be part of the same series
    // Now we can expand by looping the series
    // Fill the ouput with the expansion
    // If any of the above criteria is not met fill output with the original input char
    // Move to the next char
}


typedef struct test_data {
    char input[MAX_SIZE_INPUT];
    char output[MAX_SIZE_OUTPUT];
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
    bool debug = true;
    
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
        char output[MAX_SIZE_OUTPUT] = {0};
        
        if (debug) {
            printf("input = %s\n", arr[i].input);
        }
        
        // expand(arr[i].input, output);
        
        if (debug) {
            printf("input = %s, output = %s, expected = %s\n", arr[i].input, output, arr[i].output);
        }
        // if (!compare_string(output, arr[i].output)) {
        //     printf("input = %s, output = %s, expected = %s\n", arr[i].input, output, arr[i].output);
        //     ++num_failed;
        // }
    }
    if (num_failed > 0) {
        printf("%d test failed\n", num_failed);
    } else {
        printf("All tests passed\n");
    }
    printf("Done\n");

    return 0;
}
