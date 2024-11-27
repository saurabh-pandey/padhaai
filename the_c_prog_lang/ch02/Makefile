CC=gcc
CFLAGS=-Wall -g

BIN=bin
$(shell mkdir -p $(BIN))

JUST_EXECS = simple_atoi simple_test simple_tolower simple_htoi squeeze any print_bits getbits \
invert_bits right_rotate_bits bitcount
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

$(BIN)/right_rotate_bits : right_rotate_bits.c bits_helper.c bits_helper.h
	$(CC) $(CFLAGS) -o $@ $^

$(BIN)/bitcount : bitcount.c bits_helper.c bits_helper.h
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -r $(BIN)

test:
	@echo "Running tests\n"
	@$(foreach exec, $(EXECS), ./$(exec) && echo ;)
