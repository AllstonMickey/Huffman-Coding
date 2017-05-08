CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=c99 -g
RM = rm -f
MASK = -DMASK=0x00ffffff
OBJECTS = bv.o minsort.o bubblesort.o insertionsort.o quicksort.o mergesort.o sorting.o
HEADERS = bv.h minsort.h bubblesort.h insertionsort.h quicksort.h mergesort.h

.PHONY: all
all : sorting

sorting : $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o sorting

sorting.o : sorting.c $(HEADERS)
	$(CC) $(CFLAGS) $(MASK) sorting.c -c

mergesort.o : mergesort.c mergesort.h
	$(CC) $(CFLAGS) mergesort.c -c

quicksort.o : quicksort.c quicksort.h
	$(CC) $(CFLAGS) quicksort.c -c

insertionsort.o : insertionsort.c insertionsort.h
	$(CC) $(CFLAGS) insertionsort.c -c

bubblesort.o : bubblesort.c bubblesort.h
	$(CC) $(CFLAGS) bubblesort.c -c

minsort.o : minsort.c minsort.h
	$(CC) $(CFLAGS) minsort.c -c

bv.o : bv.c bv.h
	$(CC) $(CFLAGS) bv.c -c

.PHONY: clean
clean :
	$(RM) $(OBJECTS) sorting
