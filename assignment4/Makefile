CC = gcc
CFLAGS = -Wall -Werror -Wextra -Wpedantic -std=c99
RM = rm -f

.PHONY: all
all : encode

encode : encode.o huffman.o queue.o
	$(CC) $(CFLAGS) encode.o huffman.o queue.o -o encode

encode.o : encode.c code.h huffman.h queue.h
	$(CC) $(CFLAGS) encode.c -c

huffman.o : huffman.c huffman.h code.h
	$(CC) $(CFLAGS) huffman.c -c

queue.o : queue.c queue.h huffman.h
	$(CC) $(CFLAGS) queue.c -c

.PHONY: clean
clean :
	$(RM) queue.o huffman.o encode.o encode
