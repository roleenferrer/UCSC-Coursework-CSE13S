CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic -std=c99

all: hatterspeak

hatterspeak: hatterspeak.o speck.o bv.o bf.o ll.o hash.o parser.o
	$(CC) -o hatterspeak hatterspeak.o speck.o bv.o bf.o ll.o hash.o parser.o 

hatterspeak.o: hatterspeak.c
	$(CC) $(CFLAGS) -c hatterspeak.c

speck.o: speck.c
	$(CC) $(CFLAGS) -c speck.c

bv.o: bv.c
	$(CC) $(CFLAGS) -c bv.c

bf.o: bf.c
	$(CC) $(CFLAGS) -c bf.c

ll.o: ll.c
	$(CC) $(CFLAGS) -c ll.c

hash.o: hash.c
	$(CC) $(CFLAGS) -c hash.c

parser.o: parser.c
	$(CC) $(CFLAGS) -c parser.c

clean:
	rm -rf hatterspeak hatterspeak.o speck.o bv.o bf.o ll.o hash.o parser.o infer-out

infer:
	make clean; infer-capture -- make; infer-analyze -- make