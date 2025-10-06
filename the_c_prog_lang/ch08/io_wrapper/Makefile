CC=gcc
CFLAGS=-Wall -g

BIN=bin
$(shell mkdir -p $(BIN))

LIB=lib
$(shell mkdir -p $(LIB))

all: $(LIB)/libio_wrapper.so $(BIN)/try_wrapper

$(LIB)/libio_wrapper.so : io_wrapper.c
	$(CC) $(CFLAGS) -fPIC -shared -o $@ $^

$(BIN)/try_wrapper : try_wrapper.c
	$(CC) $(CFLAGS) -Llib -o $@ $^ -lio_wrapper

.PHONY: clean
clean:
	rm -r $(BIN) $(LIB)

# Run tests
test:
	python3 -m unittest -v