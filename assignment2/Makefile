CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=c99
RM = rm -f
MASK = -DMASK=0x00ffffff
OBJECTS = bv.o minsort.o bubblesort.o sorting.o
HEADERS = bv.h minsort.h bubblesort.h

.PHONY: all
all : sorting

sorting : $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o sorting

sorting.o : sorting.c $(HEADERS)
	$(CC) $(CFLAGS) $(MASK) sorting.c -c

bubblesort.o : bubblesort.c bubblesort.h
	$(CC) $(CFLAGS) bubblesort.c -c

minsort.o : minsort.c minsort.h
	$(CC) $(CFLAGS) minsort.c -c

bv.o : bv.c bv.h
	$(CC) $(CFLAGS) bv.c -c

.PHONY: clean
clean :
	$(RM) $(OBJECTS) sorting
