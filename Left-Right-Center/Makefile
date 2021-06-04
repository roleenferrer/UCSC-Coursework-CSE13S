CFLAGS = -Wall -Wextra -Werror -pedantic
CC = clang $(CFLAGS)

lrc	:	lrc.o
	$(CC) -o lrc lrc.o
lrc.o	:	lrc.c
	$(CC) -c lrc.c
clean	:
	rm -f lrc lrc.o
infer	:
	make clean; infer-capture -- make; infer-analyze -- make
