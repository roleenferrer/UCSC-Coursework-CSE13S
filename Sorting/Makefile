CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic

all: sorting

sorting: sorting.o bubble.o shell.o quick.o binary.o
	$(CC) -o sorting sorting.o bubble.o shell.o quick.o binary.o -lm

sorting.o: sorting.c
	$(CC) $(CFLAGS) -c sorting.c

bubble.o: bubble.c bubble.h
	$(CC) $(CFLAGS) -c bubble.c

shell.o: shell.c shell.h
	$(CC) $(CFLAGS) -c shell.c

quick.o: quick.c quick.h
	$(CC) $(CFLAGS) -c quick.c

binary.o: binary.c binary.h
	$(CC) $(CFLAGS) -c binary.c

clean:
	rm -rf sorting sorting.o bubble.o shell.o quick.o binary.o infer-out

valgrind:
	make all; valgrind ./sorting -A

infer:
	make clean; infer-capture -- make; infer-analyze -- make