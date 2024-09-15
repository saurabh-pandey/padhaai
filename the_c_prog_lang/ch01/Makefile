CC=gcc
CFLAGS := -Wall

BIN=bin

$(shell mkdir -p $(BIN))

SRCS=$(wildcard *.c)
BINS=$(SRCS:%.c=%)
LIST=$(addprefix $(BIN)/, $(BINS))

# %.o: %.c
# 	$(CC) -c -o $@

$(BIN)/%: %.o
	$(CC) $(CFLAGS) -o $@ $^

all: $(LIST)

debug : CFLAGS += -g
debug : all

clean:
	rm -r $(BIN)

test:
	python3 -m unittest -v
