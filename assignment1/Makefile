RM = rm -f
CC = gcc $(CFLAGS)
CFLAGS = -Wall -Werror -Wextra -pedantic -std=c99
OBJECTS = parfait.o bv.o sieve.o

.PHONY: all
all : parfait

parfait: parfait.o
	$(CC) parfait.o -o parfait

parfait.o : parfait.c
	$(CC) -c parfait.c

sieve.o : sieve.c sieve.h
	$(CC) -c sieve.c -lm

bv.o : bv.c bv.c
	$(CC) -c bv.c

.PHONY: clean
clean:
	$(RM) $(OBJECTS) parfait
