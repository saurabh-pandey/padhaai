CHAPTERS = ch01 ch02 ch03 ch04 ch05 ch06 ch07

all:
	@echo "Building everything"
	$(foreach var, $(CHAPTERS), cd $(var) && $(MAKE) all && cd ..;)

test:
	@echo "Running all tests"
	$(foreach var, $(CHAPTERS), cd $(var) && $(MAKE) test && cd ..;)

clean:
	@echo "Cleaning"
	$(foreach var, $(CHAPTERS), cd $(var) && $(MAKE) clean && cd ..;)

