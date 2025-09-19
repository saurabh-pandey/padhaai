#ifndef TCPL_CH08_IO_WRAPPER_H
#define TCPL_CH08_IO_WRAPPER_H

// Opaque File Handle
typedef struct MY_FILE MY_FILE;

// Probe functions
void print_file_table(const char*prefix);
int count_open_fds();

// Actual file IO
MY_FILE *my_fopen(const char *pathname, const char *mode);
int my_fgetc(MY_FILE *stream);
int my_fflush(MY_FILE *stream);
int my_fputc(int c, MY_FILE *stream);
int my_fseek(MY_FILE *stream, long offset, int whence);
int my_fclose(MY_FILE *stream);


#endif // TCPL_CH08_IO_WRAPPER_H
