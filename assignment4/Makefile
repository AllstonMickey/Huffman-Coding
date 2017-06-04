CC = gcc
CFLAGS = -Wall -Werror -Wextra -Wpedantic -std=c99
RM = rm -f

.PHONY: all
all : encode decode

encode : encode.o huffman.o queue.o
	$(CC) $(CFLAGS) encode.o huffman.o queue.o -o encode

encode.o : encode.c code.h huffman.h queue.h
	$(CC) $(CFLAGS) encode.c -c

decode : decode.o stack.o huffman.o
	$(CC) -std=c99 decode.o stack.o huffman.o -o decode

decode.o : decode.c stack.h huffman.h
	$(CC) -std=c99 decode.c -c

stack.o : stack.c stack.h huffman.h
	$(CC) -std=c99 stack.c -c

huffman.o : huffman.c huffman.h code.h
	$(CC) $(CFLAGS) huffman.c -c

queue.o : queue.c queue.h huffman.h
	$(CC) $(CFLAGS) queue.c -c

.PHONY: clean
clean :
	$(RM) queue.o huffman.o stack.o encode.o decode.o encode decode
