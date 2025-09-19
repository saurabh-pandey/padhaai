CC=gcc
CFLAGS=-Wall -g

BIN=bin
$(shell mkdir -p $(BIN))

$(BIN)/io_wrapper : io_wrapper.c
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -r $(BIN)

all: $(BIN)/io_wrapper

# Run tests
test:
	python3 -m unittest -v