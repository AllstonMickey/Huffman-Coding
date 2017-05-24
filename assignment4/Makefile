CC = gcc
CFLAGS = -Wall -Werror -Wextra -Wpedantic -std=c99
RM = rm -f

.PHONY: all
all : test

test : test.o stack.o
	$(CC) -std=c99 test.o stack.o -o test

test.o : test.c stack.h
	$(CC) -std=c99 test.c -c

stack.o : stack.c stack.h
	$(CC) -std=c99 stack.c -c

.PHONY: clean
clean :
	$(RM) test.o test stack.o
