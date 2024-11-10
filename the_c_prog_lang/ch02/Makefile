CC=gcc
CFLAGS=-Wall

BIN=bin
$(shell mkdir -p $(BIN))

JUST_EXECS = simple_atoi simple_test simple_tolower
EXECS=$(addprefix $(BIN)/, $(JUST_EXECS))

$(BIN)/% : $(BIN)/%.o
	$(CC) $(CFLAGS) -o $@ $^

$(BIN)/%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $^

all: $(EXECS)

$(BIN)/simple_test : simple_test.c my_add.c my_add.h
	$(CC) $(CFLAGS) -o $@ $^ -I.

$(BIN)/simple_atoi : simple_atoi.c
	$(CC) $(CFLAGS) -o $@ $^ -lm

.PHONY: clean
clean:
	rm -r $(BIN)

test:
	@echo "Running tests\n"
	@$(foreach exec, $(EXECS), ./$(exec) && echo ;)
