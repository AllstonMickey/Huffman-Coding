RM = rm -f
CC = gcc $(CFLAGS)
CFLAGS = -Wall -Werror -Wextra -pedantic -std=c99
OBJECTS = bv.o sieve.o

.PHONY: all
all : parfait

parfait : $(OBJECTS)
	$(CC) $(OBJECTS) -o parfait

sieve.o : sieve.c sieve.h
	$(CC) -c sieve.c -lm

bv.o : bv.c bv.c
	$(CC) -c bv.c

.PHONY: clean
clean:
	$(RM) $(OBJECTS) parfait
