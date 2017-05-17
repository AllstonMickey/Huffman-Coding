CC = gcc
CFLAGS = -Wall -Werror -Wextra -Wpedantic -std=c99
MASK= -DMASK=0x0000FFFF
RM = rm -f
HEADERS = bf.h hash.h aes.h ll.h strClone.h
OBJECTS = test.o aes.o ll.o

.PHONY: all
all : test

test : $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o test

test.o : test.c $(HEADERS)
	$(CC) $(CFLAGS) $(MASK) test.c -c

aes.o : aes.c aes.h
	$(CC) $(CFLAGS) aes.c -c

ll.o : ll.c ll.h
	$(CC) $(CFLAGS) ll.c -c

.PHONY: clean
clean :
	$(RM) test $(OBJECTS)
