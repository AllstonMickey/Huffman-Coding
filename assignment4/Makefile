CC = gcc
CFLAGS = -Wall -Werror -Wextra -Wpedantic -std=c99
RM = rm -f
STACKTYPE := uint64_t

.PHONY: all
all : test

test : test.o stack.o queue.o
	$(CC) -DSTACK_ITEM=$(STACKTYPE) -std=c99 test.o stack.o stackType.o queue.o -o test

test.o : test.c stack.h queue.h
	$(CC) -DSTACK_ITEM=$(STACKTYPE) -std=c99 test.c -c

stack.o : stack.c stack.h
	$(CC) -DSTACK_ITEM=$(STACKTYPE) -std=c99 stack.c -c

queue.o : queue.c queue.h
	$(CC) -std=c99 queue.c -c

.PHONY: clean
clean :
	$(RM) test.o stack.o queue.o test
