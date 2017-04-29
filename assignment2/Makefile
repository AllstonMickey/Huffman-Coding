CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=c99
RM = rm -f
MASK = -DMASK=0x00ffffff
OBJECTS = bv.o minsort.o sorting.o
HEADERS = bv.h minsort.h

.PHONY: all
all : sorting

sorting : $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o sorting

sorting.o : sorting.c $(HEADERS)
	$(CC) $(CFLAGS) sorting.c -c

minsort : minsort.o
	$(CC) $(CFLAGS) minsort.o -o minsort

minsort.o : minsort.c minsort.h
	$(CC) $(CFLAGS) minsort.c -c

bv : bv.o
	$(CC) $(CFLAGS) bv.o -o bv

bv.o : bv.c bv.h
	$(CC) $(CFLAGS) bv.c -c

.PHONY: clean
clean :
	$(RM) $(OBJECTS) sorting
