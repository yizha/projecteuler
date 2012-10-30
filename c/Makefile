.phony: clean run

CC=gcc

run: test
	$(CURDIR)/test

test: main.c
	$(CC) -std=c99 -lm -o test main.c

clean:
	rm -f test
