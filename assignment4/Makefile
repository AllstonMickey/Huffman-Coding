CC = gcc
CFLAGS = -Wall -Werror -Wextra -Wpedantic -std=c99
RM = rm -f

DEFINE_QUEUE     = -DQUEUE_ITEM=treeNode

.PHONY: all
all : encode

encode : encode.o huffman.o queue.o
	$(CC) -std=c99 encode.o huffman.o queue.o -o encode

encode.o : encode.c code.h huffman.h queue.h
	$(CC) $(DEFINE_QUEUE) -std=c99 encode.c -c

decode : decode.o stack.item.o
	$(CC) -std=c99 decode.o stack.item.o -o decode

decode.o : decode.c stack.item.h
	$(CC) -std=c99 decode.c -c

stack.item.o : stack.item.c stack.item.h
	$(CC) -std=c99 stack.item.c -c

stack.o : stack.c stack.h
	$(CC) -std=c99 stack.c -c

huffman.o : huffman.c huffman.h stack.h
	$(CC) -std=c99 huffman.c -c

queue.o : queue.c queue.h huffman.h
	$(CC) $(DEFINE_QUEUE) -include huffman.h -std=c99 queue.c -c

.PHONY: clean
clean :
	$(RM) queue.o huffman.o encode.o encode
