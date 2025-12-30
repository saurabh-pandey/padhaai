CC=gcc
CFLAGS=-Wall -g

BIN=bin
$(shell mkdir -p $(BIN))

JUST_EXECS = initial_experiments object_pool try_storage_allocator
EXECS=$(addprefix $(BIN)/, $(JUST_EXECS))

$(BIN)/% : $(BIN)/%.o
	$(CC) $(CFLAGS) -o $@ $^

$(BIN)/%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $^

all: $(EXECS)

$(BIN)/try_storage_allocator: try_storage_allocator.c
	$(CC) $(CFLAGS) -Iinclude -o $@ $^

$(BIN)/initial_experiments:
	cd initial_experiments && $(MAKE) all && cd ..;

$(BIN)/object_pool:
	cd object_pool && $(MAKE) all && cd ..;

.PHONY: clean
clean:
	cd initial_experiments && $(MAKE) clean && cd ..;
	cd object_pool && $(MAKE) clean && cd ..;
	rm -r $(BIN)

# Run tests
test:
	cd initial_experiments && $(MAKE) test && cd ..;
	cd object_pool && $(MAKE) test && cd ..;
	python3 -m unittest -v