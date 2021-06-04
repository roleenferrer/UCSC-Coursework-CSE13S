CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic

all: tower

tower: tower.o stack.o
	$(CC) -o tower tower.o stack.o -lm

tower.o: tower.c
	$(CC) $(CFLAGS) -c tower.c

stack.o: stack.c stack.h
	$(CC) $(CFLAGS) -c stack.c

clean:
	rm -rf tower tower.o stack.o infer-out

infer:
	make clean; infer-capture -- make; infer-analyze -- make