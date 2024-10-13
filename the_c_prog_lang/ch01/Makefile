# Select compiler
CC=gcc
# Compiler flags
CFLAGS := -Wall

# Build directory name
BIN=bin

# Create build directory
$(shell mkdir -p $(BIN))

# List of all source files
SRCS=$(wildcard *.c)

# Filter only filenames as they become exe
BINS=$(SRCS:%.c=%)

# Append bin folder as suffix where the exes are dumped
LIST=$(addprefix $(BIN)/, $(BINS))

# Rule to compile object from source
$(BIN)/%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^

# Rule to make exe from object
$(BIN)/%: $(BIN)/%.o
	$(CC) $(CFLAGS) -o $@ $^

# Build everything
all: $(LIST)

# Debug mode
debug : CFLAGS += -g
debug : all

# Clean is not a file
.PHONY: clean
# Clean
clean:
	rm -r $(BIN)

# Run tests
test:
	python3 -m unittest -v
