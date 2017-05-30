CC = gcc
CFLAGS = -Wall -Werror -Wextra -Wpedantic -std=c99
RM = rm -f

ENCODE_STACKTYPE = uint8_t
DECODE_STACKTYPE = uint16_t
STACKTYPE        = uint32_t
DEFINE_STACK     = -DSTACK_ITEM=$(STACKTYPE)

QUEUETYPE    = uint32_t
DEFINE_QUEUE = -DQUEUE_ITEM=$(QUEUETYPE)

.PHONY: all
all : test

test : test.o stack.o queue.o huffman.o
	$(CC) -std=c99 test.o stack.o queue.o huffman.o -o test

test.o : test.c stack.h queue.h heap.h bv.h huffman.h
	$(eval STACKTYPE=$(ENCODE_STACKTYPE))
	$(eval QUEUETYPE=uint32_t)
	$(CC) $(DEFINE_STACK) $(DEFINE_QUEUE) -std=c99 test.c -c

huffman.o : huffman.c huffman.h
	$(CC) $(DEFINE_STACK) -std=c99 huffman.c -c

stack.o : stack.c stack.h
	$(CC) $(DEFINE_STACK) -std=c99 stack.c -c

queue.o : queue.c queue.h heap.h
	$(CC) $(DEFINE_QUEUE) -std=c99 queue.c -c

.PHONY: clean
clean :
	$(RM) test.o stack.o queue.o huffman.o test encode.o encode
