RM = rm -f
CC = gcc $(CFLAGS)
CFLAGS = -Wall -Werror -Wextra -pedantic -std=c99
OBJECTS = parfait.o bv.o sieve.o

.PHONY: all
all : parfait

parfait: $(OBJECTS)
	$(CC) $(OBJECTS) -o parfait -lm

parfait.o : parfait.c sieve.h
	$(CC) -c parfait.c

bv.o : bv.c bv.h
	$(CC) -c bv.c

sieve.o : sieve.c sieve.h
	$(CC) -c sieve.c

.PHONY: clean
clean:
	$(RM) $(OBJECTS) parfait
