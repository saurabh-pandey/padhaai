CC=gcc
CFLAGS=-Wall -g

BIN=bin
$(shell mkdir -p $(BIN))


JUST_EXECS = binary_search shell_sort reverse_string expand
EXECS=$(addprefix $(BIN)/, $(JUST_EXECS))

$(BIN)/% : $(BIN)/%.o
	$(CC) $(CFLAGS) -o $@ $^

$(BIN)/%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $^

all: $(EXECS)


.PHONY: clean
clean:
	rm -r $(BIN)

test:
	@echo "Running tests\n"
	@$(foreach exec, $(EXECS), ./$(exec) && echo ;)
