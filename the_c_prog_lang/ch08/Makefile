CC=gcc
CFLAGS=-Wall -g

BIN=bin
$(shell mkdir -p $(BIN))


JUST_EXECS = in_out unbuf_getchar buf_getchar sys_cp sys_cat read_n_bytes
EXECS=$(addprefix $(BIN)/, $(JUST_EXECS))

$(BIN)/% : $(BIN)/%.o
	$(CC) $(CFLAGS) -o $@ $^

$(BIN)/%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $^

all: $(EXECS)


.PHONY: clean
clean:
	rm -r $(BIN)

# Run tests
test:
	python3 -m unittest -v

