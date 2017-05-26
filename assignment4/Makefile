CC = gcc
CFLAGS = -Wall -Werror -Wextra -Wpedantic -std=c99
RM = rm -f
STACKTYPE = uint8_t
QUEUETYPE = uint8_t
DEFSTACK  = -DSTACK_ITEM=$(STACKTYPE)
DEFQUEUE  = -DQUEUE_ITEM=$(QUEUETYPE)

.PHONY: all
all : test

test : test.o stack.o queue.o
	$(CC) -std=c99 test.o stack.o queue.o -o test

test.o : test.c stack.h queue.h
	$(eval STACKTYPE=uint16_t)
	$(eval QUEUETYPE=uint16_t)
	$(CC) $(DEFSTACK) $(DEFQUEUE) -std=c99 test.c -c

stack.o : stack.c stack.h
	$(CC) $(DEFSTACK) -std=c99 stack.c -c

queue.o : queue.c queue.h
	$(CC) $(DEFQUEUE) -std=c99 queue.c -c

.PHONY: clean
clean :
	$(RM) test.o stack.o queue.o test
