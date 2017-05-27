CC = gcc
CFLAGS = -Wall -Werror -Wextra -Wpedantic -std=c99
RM = rm -f

ENCODE_STACKTYPE = uint8_t
DECODE_STACKTYPE = uint16_t
STACKTYPE        = uint32_t
DEFINE_STACK     = -DSTACK_ITEM=$(STACKTYPE)

QUEUETYPE    = uint8_t
DEFINE_QUEUE = -DQUEUE_ITEM=$(QUEUETYPE)

.PHONY: all
all : test

test : test.o stack.o queue.o
	$(CC) -std=c99 test.o stack.o queue.o -o test

test.o : test.c stack.h queue.h heap.h bv.h
	$(eval STACKTYPE=$(ENCODE_STACKTYPE))
	$(CC) $(DEFINE_STACK) $(DEFINE_QUEUE) -std=c99 test.c -c

stack.o : stack.c stack.h
	$(CC) $(DEFINE_STACK) -std=c99 stack.c -c

queue.o : queue.c queue.h heap.h
	$(CC) $(DEFINE_QUEUE) -std=c99 queue.c -c

.PHONY: clean
clean :
	$(RM) test.o stack.o queue.o test
