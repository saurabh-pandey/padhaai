#include <stdbool.h>
#include <stdio.h>

#define MAX_SIZE_INPUT 20
#define MAX_SIZE_OUTPUT 100


typedef struct series {
    char data[100];
} series;


series supported_series[] = {
    {"abcdefghijklmnopqrstuvwxyz"},
    {"0123456789"}
};


typedef struct search_result {
    int series_index;
    int data_index;
} search_result;



search_result search(char val) {
    search_result result = {-1, -1};
    for (int i = 0; i < sizeof(supported_series)/sizeof(series); ++i) {
        for (int j = 0; supported_series[i].data[j] != '\0'; ++j) {
            if (val == supported_series[i].data[j]) {
                result.series_index = i;
                result.data_index = j;
                return result;
            }
        }
    }
    return result;
}

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
    int i = 0;
    int j = 0;
    while (input[i] != '\0') {
        if (input[i] == '-') {
            if (i == 0) {
                output[j] = input[i];
                ++i;
                ++j;
            } else if (input[i + 1] == '\0') {
                output[j] = input[i];
                ++i;
                ++j;
            } else {
                char left_char = input[i - 1];
                search_result left_char_search_res = search(left_char);
                if (left_char_search_res.series_index == -1) {
                    output[j] = input[i - 1];
                    ++j;
                    output[j] = input[i];
                    ++i;
                    ++j;
                    output[j] = input[i];
                    ++i;
                    ++j;
                    continue;
                } else if (left_char_search_res.data_index == -1) {
                    output[j] = input[i - 1];
                    ++j;
                    output[j] = input[i];
                    ++i;
                    ++j;
                    output[j] = input[i];
                    ++i;
                    ++j;
                    continue;
                }
                char right_char = input[i + 1];
                search_result right_char_search_res = search(right_char);
                if (right_char_search_res.series_index == -1) {
                    output[j] = input[i - 1];
                    ++j;
                    output[j] = input[i];
                    ++i;
                    ++j;
                    output[j] = input[i];
                    ++i;
                    ++j;
                    continue;
                } else if (right_char_search_res.data_index == -1) {
                    output[j] = input[i - 1];
                    ++j;
                    output[j] = input[i];
                    ++i;
                    ++j;
                    output[j] = input[i];
                    ++i;
                    ++j;
                    continue;
                } else if (left_char_search_res.series_index != right_char_search_res.series_index) {
                    output[j] = input[i - 1];
                    ++j;
                    output[j] = input[i];
                    ++i;
                    ++j;
                    output[j] = input[i];
                    ++i;
                    ++j;
                    continue;
                } else if (left_char_search_res.data_index > right_char_search_res.data_index) {
                    output[j] = input[i - 1];
                    ++j;
                    output[j] = input[i];
                    ++i;
                    ++j;
                    output[j] = input[i];
                    ++i;
                    ++j;
                    continue;
                } else {
                    const int series_index = left_char_search_res.series_index;
                    const int data_start_index = left_char_search_res.data_index;
                    const int data_end_index = right_char_search_res.data_index;
                    for (int it = data_start_index; it <= data_end_index; ++it) {
                        output[j] = supported_series[series_index].data[it];
                        ++j;
                    }
                    i += 2;
                }
            }
        } else if (input[i + 1] != '-') {
            output[j] = input[i];
            ++i;
            ++j;
        } else {
            ++i;
        }
    }
    output[j] = '\0';
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
        char output[MAX_SIZE_OUTPUT] = {0};
        
        if (debug) {
            printf("input = %s\n", arr[i].input);
        }
        
        expand(arr[i].input, output);
        
        if (debug) {
            printf("input = %s, output = %s, expected = %s\n", arr[i].input, output, arr[i].output);
        }
        if (!compare_string(output, arr[i].output)) {
            printf("Failed input = %s, output = %s, expected = %s\n",
                   arr[i].input,
                   output,
                   arr[i].output);
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
