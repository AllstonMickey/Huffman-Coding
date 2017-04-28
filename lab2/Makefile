CC = gcc
CFLAGS = -Wall -Werror -Wextra -Wpedantic -std=c99
RM = rm -f

.PHONY: all
all : arraylist
	
arraylist : arraylist.o
	$(CC) $(CFLAGS) arraylist.o -o arraylist

arraylist.o : arraylist.c
	$(CC) $(CFLAGS) arraylist.c -c

.PHONY: clean
clean :
	$(RM) arraylist.o arraylist

