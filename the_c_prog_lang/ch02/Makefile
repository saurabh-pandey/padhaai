CC=gcc
CFLAGS=-Wall

BIN=bin
$(shell mkdir -p $(BIN))

$(BIN)/% : $(BIN)/%.o
	$(CC) $(CFLAGS) -o $@ $^

$(BIN)/%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $^

all: $(BIN)/simple_atoi $(BIN)/simple_test

$(BIN)/simple_test : simple_test.c my_add.c
	$(CC) $(CFLAGS) -o $@ $^ -I.


.PHONY: clean
clean:
	rm -r $(BIN)

EXES = $(BIN)/simple_atoi $(BIN)/simple_test

test:
	@echo "Running tests\n"
	@$(foreach var, $(EXES), ./$(var) && echo ;)
