CC=gcc
CFLAGS=-Wall -g

BIN=bin
$(shell mkdir -p $(BIN))

$(BIN)/rpn : main.c parser.c stack.c
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -r $(BIN)

all: $(BIN)/rpn

# Run tests
test:
	python3 -m unittest -v