CC=gcc
CFLAGS=-Wall -g

BIN=bin
$(shell mkdir -p $(BIN))

JUST_EXECS = experiments try_vec_object_pool_constant try_vec_object_pool_linear
EXECS=$(addprefix $(BIN)/, $(JUST_EXECS))

$(BIN)/% : $(BIN)/%.o
	$(CC) $(CFLAGS) -o $@ $^

$(BIN)/%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $^

all: $(EXECS)

$(BIN)/try_vec_object_pool_constant: CFLAGS +=
$(BIN)/try_vec_object_pool_linear:   CFLAGS += -DYIELD_LINEAR

$(BIN)/try_vec_object_pool_%: try_vec_object_pool.c linear_vec_pool.c
	$(CC) $(CFLAGS) -Iinclude -o $@ $^

.PHONY: clean
clean:
	rm -r $(BIN)

# Run tests
test:
	python3 -m unittest -v