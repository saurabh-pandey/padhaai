CC=gcc
CFLAGS=-Wall -g

BIN=bin
$(shell mkdir -p $(BIN))


JUST_EXECS = in_out unbuf_getchar buf_getchar sys_cp sys_cat lseek_trials read_nbytes_offset
EXECS=$(addprefix $(BIN)/, $(JUST_EXECS))

$(BIN)/% : $(BIN)/%.o
	$(CC) $(CFLAGS) -o $@ $^

$(BIN)/%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $^

all: $(EXECS) iow fs

iow:
	cd io_wrapper && $(MAKE) all && cd ..;

fs:
	cd fsize && $(MAKE) all && cd ..;


.PHONY: clean
clean:
	rm -r $(BIN)
	cd io_wrapper && $(MAKE) clean && cd ..;
	cd fsize && $(MAKE) clean && cd ..;

# Run tests
test:
	python3 -m unittest -v
	cd io_wrapper && $(MAKE) test && cd ..;
	cd fsize && $(MAKE) test && cd ..;

