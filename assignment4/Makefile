CC = gcc
CFLAGS = -Wall -Werror -Wextra -Wpedantic -std=c99
RM = rm -f

ENCODE_STACKTYPE = uint8_t
DECODE_STACKTYPE = uint16_t
STACKTYPE        = uint32_t
DEFINE_STACK     = -DSTACK_ITEM=$(STACKTYPE)

QUEUETYPE    = treeNode
DEFINE_QUEUE = -DQUEUE_ITEM=$(QUEUETYPE)

.PHONY: all
all : encode

encode : encode.o stack.o huffman.o queue.o
	$(CC) -std=c99 encode.o stack.o huffman.o queue.o -o encode

encode.o : encode.c stack.h huffman.h queue.h
	$(eval STACKTYPE=$(ENCODE_STACKTYPE))
	$(CC) $(DEFINE_STACK) $(DEFINE_QUEUE) -std=c99 encode.c -c

stack.o : stack.c stack.h
	$(CC) $(DEFINE_STACK) -std=c99 stack.c -c

huffman.o : huffman.c huffman.h stack.h
	$(CC) $(DEFINE_STACK) -std=c99 huffman.c -c

queue.o : queue.c queue.h huffman.h
	$(CC) $(DEFINE_STACK) $(DEFINE_QUEUE) -include huffman.h -std=c99 queue.c -c

.PHONY: clean
clean :
	$(RM) test.o stack.o queue.o huffman.o test encode.o encode
