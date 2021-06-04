CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic

all: sequence

sequence: sequence.o bv.o sieve.o
	$(CC) -o sequence sequence.o bv.o sieve.o -lm

sequence.o: sequence.c
	$(CC) $(CFLAGS) -c sequence.c

bv.o: bv.c bv.h
	$(CC) $(CFLAGS) -c bv.c

sieve.o: sieve.c sieve.h
	$(CC) $(CFLAGS) -c sieve.c

clean:
	rm -rf sequence sequence.o bv.o sieve.o infer-out

infer:
	make clean; infer-capture -- make; infer-analyze -- make