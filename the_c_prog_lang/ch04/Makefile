CC=gcc
CFLAGS=-Wall -g

BIN=bin
$(shell mkdir -p $(BIN))


JUST_EXECS = simple_pattern_search simple_strrindex simple_atof reverse_polish_calc \
recursive_printd simple_quick_sort
EXECS=$(addprefix $(BIN)/, $(JUST_EXECS))

$(BIN)/% : $(BIN)/%.o
	$(CC) $(CFLAGS) -o $@ $^

$(BIN)/%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $^

all: $(EXECS) rpn

rpn:
	cd reverse_polish_book && $(MAKE) all && cd ..;

.PHONY: clean
clean:
	rm -r $(BIN)
	cd reverse_polish_book && $(MAKE) clean && cd ..;

# Run tests
test:
	python3 -m unittest -v
	cd reverse_polish_book && $(MAKE) test && cd ..;

