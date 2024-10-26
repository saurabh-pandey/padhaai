CC=gcc
CFLAGS=-Wall

BIN=bin
$(shell mkdir -p $(BIN))

JUST_EXECS = simple_atoi simple_test
EXECS=$(addprefix $(BIN)/, $(JUST_EXECS))

$(BIN)/% : $(BIN)/%.o
	$(CC) $(CFLAGS) -o $@ $^

$(BIN)/%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $^

all: $(EXECS)

$(BIN)/simple_test : simple_test.c my_add.c
	$(CC) $(CFLAGS) -o $@ $^ -I.


.PHONY: clean
clean:
	rm -r $(BIN)

test:
	@echo "Running tests\n"
	@$(foreach exec, $(EXECS), ./$(exec) && echo ;)
