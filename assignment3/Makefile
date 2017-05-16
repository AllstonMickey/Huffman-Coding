CC = gcc
CFLAGS = -Wall -Werror -Wextra -Wpedantic -std=c99
RM = rm -f
HEADERS = bf.h hash.h aes.h
OBJECTS = test.o aes.o

.PHONY: all
all : test

test : $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o test

test.o : test.c bf.h hash.h aes.h
	$(CC) $(CFLAGS) test.c -c

aes.o : aes.c aes.h
	$(CC) $(CFLAGS) aes.c -c

.PHONY: clean
clean :
	$(RM) aes.o test.o test
