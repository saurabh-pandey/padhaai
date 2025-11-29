CC=gcc
CFLAGS=-Wall -g
# LDFLAGS  := -Llib -Wl,-rpath='$$ORIGIN/../lib'

BIN=bin
$(shell mkdir -p $(BIN))

# LIB=lib
# $(shell mkdir -p $(LIB))

all: $(BIN)/experiments

# $(LIB)/libio_wrapper.so : io_wrapper.c
# 	$(CC) $(CFLAGS) -fPIC -shared -o $@ $^

$(BIN)/experiments : experiments.c
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -r $(BIN)

# Run tests
test:
	python3 -m unittest -v