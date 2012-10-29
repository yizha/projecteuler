.phony: clean

CC=gcc

run: clean test
	$(CURDIR)/test

test: 
	$(CC) -std=c99 -lm -o test main.c

clean:
	rm -f test
