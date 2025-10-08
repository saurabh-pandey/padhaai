#include <stdio.h>

#include <string.h> // strcmp()

#include "io_wrapper.h"


#define PRINT_BUFFER_SIZE 100
#define NUM_FILES_WITHIN_LIMITS 3


// Data used to test read, write and append tests
const char * data = "This is a small sentence that I am going to write. Now I will explicitly\n"
                    "add a newline. It is on a newline now. Let's add some more, what,\n"
                    "punctuation marks. We have come a long way!!!";


// Test functions

int check_fd_count(int expected) {
    int actual = -1;
    if ((actual = count_open_fds()) != expected) {
        printf("ERROR: Expected open fds to be %d but actual is %d\n", expected, actual);
        return 1;
    }
    return 0;
}

int test_open_close_within_limits(int debug) {
    const char *inp_file_name = "tests/data/input.txt";
    
    if (debug) {
        print_file_table("Beginning");
    }
    
    if (check_fd_count(0) != 0) {
        return 1;
    }
    
    MY_FILE *open_files[NUM_FILES_WITHIN_LIMITS] = {NULL};
    for (int i = 0; i < NUM_FILES_WITHIN_LIMITS; ++i) {
        MY_FILE *f = my_fopen(inp_file_name, "r");
        if (f == NULL) {
            printf("ERROR: Unable to open the file %s\n", inp_file_name);
            return 1;
        } else {
            if (debug) {
                printf("Opened file = %s\n", inp_file_name);
            }
            
            open_files[i] = f;
            
            if (check_fd_count(i + 1) != 0) {
               return 1;
            }
        }
        if (debug) {
            char prefix[PRINT_BUFFER_SIZE];
            prefix[0] = '\0';
            snprintf(prefix, PRINT_BUFFER_SIZE, "After opening %d file", (i + 1));
            print_file_table(prefix);
        }
    }
    
    for (int i = 0; i < NUM_FILES_WITHIN_LIMITS; ++i) {
        if (debug) {
            char prefix[PRINT_BUFFER_SIZE];
            prefix[0] = '\0';
            snprintf(prefix, PRINT_BUFFER_SIZE, "Before closing %d file", (i + 1));
            print_file_table(prefix);
        }
        
        if (check_fd_count(NUM_FILES_WITHIN_LIMITS - i) != 0) {
            return 1;
        }
        
        my_fclose(open_files[i]);
        
        if (debug) {
            char prefix[PRINT_BUFFER_SIZE];
            prefix[0] = '\0';
            snprintf(prefix, PRINT_BUFFER_SIZE, "After closing %d file", (i + 1));
            print_file_table(prefix);
        }

        if (check_fd_count(NUM_FILES_WITHIN_LIMITS - i - 1) != 0) {
            return 1;
        }
    }

    if (debug) {
        print_file_table("End");
    }

    if (check_fd_count(0) != 0) {
        return 1;
    }

    return 0;
}


int test_create(int debug) {
    const char *new_file_name = "tests/data/creat.txt";

    if (check_fd_count(0) != 0) {
        return 1;
    }
    
    MY_FILE *f = my_fopen(new_file_name, "w");
    if (f == NULL) {
        printf("ERROR: Unable to creat the file %s\n", new_file_name);
        return 1;
    }

    if (check_fd_count(1) != 0) {
        return 1;
    }

    my_fclose(f);

    if (check_fd_count(0) != 0) {
        return 1;
    }
    
    return 0;
}


int test_append(int debug) {
    // Create a file via append mode
    const char *file_name = "tests/data/append1.txt";

    if (check_fd_count(0) != 0) {
        return 1;
    }
    
    MY_FILE *f = my_fopen(file_name, "a");
    if (f == NULL) {
        printf("ERROR: Unable to creat/open the file %s\n", file_name);
        return 1;
    }

    if (check_fd_count(1) != 0) {
        return 1;
    }

    my_fclose(f);

    if (check_fd_count(0) != 0) {
        return 1;
    }
    
    return 0;
}


int test_fputc(int debug) {
    const char *new_file_name = "tests/data/creat.txt";

    if (check_fd_count(0) != 0) {
        return 1;
    }
    
    MY_FILE *f = my_fopen(new_file_name, "w");
    if (f == NULL) {
        printf("ERROR: Unable to creat the file %s\n", new_file_name);
        return 1;
    }

    if (check_fd_count(1) != 0) {
        return 1;
    }
    
    for (int i = 0; data[i] != '\0'; ++i) {
        my_fputc(data[i], f);
    }
    
    my_fclose(f);

    if (check_fd_count(0) != 0) {
        return 1;
    }
    
    return 0;
}


int test_fgetc(int debug) {
    const char *file_name = "tests/data/creat.txt";

    MY_FILE *f = my_fopen(file_name, "r");
    if (f == NULL) {
        printf("ERROR: Unable to open the file for reading %s\n", file_name);
        return 1;
    }

    char read_data[1000];
    int i = 0;
    int c;
    while((c = my_fgetc(f)) != EOF) {
        read_data[i] = (char)c;
        ++i;
    }
    read_data[i] = '\0';

    my_fclose(f);

    if (strcmp(read_data, data) != 0) {
        printf("Read doesn't match with write :(\n");
        return 1;
    }

    if (check_fd_count(0) != 0) {
        return 1;
    }

    return 0;
}


int test_clean_append_file(int debug) {
    // Create (thus rewrite) the file that is appended next. This clears the append file of data
    // from the past run
    const char *new_file_name = "tests/data/append.txt";

    if (check_fd_count(0) != 0) {
        return 1;
    }
    
    MY_FILE *f = my_fopen(new_file_name, "w");
    if (f == NULL) {
        printf("ERROR: Unable to creat the file %s\n", new_file_name);
        return 1;
    }

    if (check_fd_count(1) != 0) {
        return 1;
    }

    my_fclose(f);

    if (check_fd_count(0) != 0) {
        return 1;
    }
    
    return 0;
}


int test_fputc_append(int debug) {
    const char *new_file_name = "tests/data/append.txt";

    if (check_fd_count(0) != 0) {
        return 1;
    }
    
    MY_FILE *f = my_fopen(new_file_name, "a");
    if (f == NULL) {
        printf("ERROR: Unable to append to the file %s\n", new_file_name);
        return 1;
    }

    if (check_fd_count(1) != 0) {
        return 1;
    }
    
    for (int i = 0; data[i] != '\0'; ++i) {
        my_fputc(data[i], f);
    }
    
    my_fclose(f);

    if (check_fd_count(0) != 0) {
        return 1;
    }
    
    return 0;
}


int test_fgetc_append(int debug) {
    const char *file_name = "tests/data/append.txt";

    MY_FILE *f = my_fopen(file_name, "r");
    if (f == NULL) {
        printf("ERROR: Unable to open the file for reading %s\n", file_name);
        return 1;
    }

    char read_data[1000];
    int i = 0;
    int c;
    while((c = my_fgetc(f)) != EOF) {
        read_data[i] = (char)c;
        ++i;
    }
    read_data[i] = '\0';

    my_fclose(f);

    if (strcmp(read_data, data) != 0) {
        printf("Read doesn't match with write :(\n");
        return 1;
    }

    if (check_fd_count(0) != 0) {
        return 1;
    }

    return 0;
}


int test_fseek(int debug) {
    const char *file_name = "tests/data/input.txt";

    MY_FILE *f = my_fopen(file_name, "r");
    if (f == NULL) {
        printf("ERROR: Unable to open the file for reading %s\n", file_name);
        return 1;
    }

    // Read full data
    char full_data[1000];
    int data_sz = 0;
    int c;
    while((c = my_fgetc(f)) != EOF) {
        full_data[data_sz] = (char)c;
        ++data_sz;
    }
    full_data[data_sz] = '\0';

    // Now read using seek at offset
    for (int offset = 1; offset < data_sz + 1; ++offset) {
        my_fseek(f, offset, SEEK_SET);
        char read_data[1000];
        int i = 0;
        int c;
        while((c = my_fgetc(f)) != EOF) {
            read_data[i] = (char)c;
            ++i;
        }
        read_data[i] = '\0';

        if (strcmp(read_data, (full_data + offset)) != 0) {
            printf("ERROR: Seek doesn't match at offset = %d\n", offset);
            return 1;
        }
    }

    my_fclose(f);

    if (check_fd_count(0) != 0) {
        return 1;
    }

    return 0;
}


int main(int argc, char *argv[]) {
    printf("Running tests for io_wrapper\n");

    int failed = 0;
    // Start all the tests
    if ((failed = test_open_close_within_limits(0)) != 0)
    {
        printf("ERROR: test_open_close_within_limits\n");
    }

    if ((failed = test_create(0)) != 0)
    {
        printf("ERROR: test_create\n");
    }

    if ((failed = test_append(0)) != 0)
    {
        printf("ERROR: test_append\n");
    }

    if ((failed = test_fputc(0)) != 0)
    {
        printf("ERROR: test_fputc\n");
    }

    if ((failed = test_fgetc(0)) != 0)
    {
        printf("ERROR: test_fgetc\n");
    }

    if ((failed = test_clean_append_file(0)) != 0)
    {
        printf("ERROR: test_clean_append_file\n");
    }

    if ((failed = test_fputc_append(0)) != 0)
    {
        printf("ERROR: test_fputc_append\n");
    }

    if ((failed = test_fgetc_append(0)) != 0)
    {
        printf("ERROR: test_fgetc_append\n");
    }

    if ((failed = test_fseek(0)) != 0)
    {
        printf("ERROR: test_fseek\n");
    }

    if (failed) {
        printf("ERROR: Failed with some tests\n");
    } else {
        printf("All tests passed\n");
    }

    printf("Done\n");

    return 0;
}
