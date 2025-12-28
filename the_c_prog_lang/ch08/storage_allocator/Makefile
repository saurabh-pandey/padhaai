CC=gcc
CFLAGS=-Wall -g

BIN=bin
$(shell mkdir -p $(BIN))

JUST_EXECS = initial_experiments try_vec_linear_pool_constant try_vec_linear_pool_linear \
try_vec_freelist_pool_v1 try_vec_freelist_pool_v2
EXECS=$(addprefix $(BIN)/, $(JUST_EXECS))

$(BIN)/% : $(BIN)/%.o
	$(CC) $(CFLAGS) -o $@ $^

$(BIN)/%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $^

all: $(EXECS)

$(BIN)/initial_experiments:
	cd initial_experiments && $(MAKE) all && cd ..;

$(BIN)/try_vec_linear_pool_constant: CFLAGS +=
$(BIN)/try_vec_linear_pool_linear:   CFLAGS += -DYIELD_LINEAR

$(BIN)/try_vec_linear_pool_%: try_vec_linear_pool.c linear_vec_pool.c
	$(CC) $(CFLAGS) -Iinclude -o $@ $^

$(BIN)/try_vec_freelist_pool_v1: try_vec_freelist_pool.c freelist_vec_pool_v1.c
	$(CC) $(CFLAGS) -Iinclude -o $@ $^

$(BIN)/try_vec_freelist_pool_v2: try_vec_freelist_pool.c freelist_vec_pool_v2.c
	$(CC) $(CFLAGS) -Iinclude -o $@ $^


.PHONY: clean
clean:
	cd initial_experiments && $(MAKE) clean && cd ..;
	rm -r $(BIN)

# Run tests
test:
	cd initial_experiments && $(MAKE) test && cd ..;
	python3 -m unittest -v