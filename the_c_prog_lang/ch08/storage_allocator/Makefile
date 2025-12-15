CC=gcc
CFLAGS=-Wall -g

BIN=bin
$(shell mkdir -p $(BIN))

JUST_EXECS = experiments test_vec_object_pool
EXECS=$(addprefix $(BIN)/, $(JUST_EXECS))

$(BIN)/% : $(BIN)/%.o
	$(CC) $(CFLAGS) -o $@ $^

$(BIN)/%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $^

$(BIN)/test_vec_object_pool : test_vec_object_pool.c linear_vec_pool.c
	$(CC) $(CFLAGS) -Iinclude -o $@ $^

all: $(EXECS)

.PHONY: clean
clean:
	rm -r $(BIN)

# Run tests
test:
	python3 -m unittest -v