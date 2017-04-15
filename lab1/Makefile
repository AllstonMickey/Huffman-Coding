RM = rm -f
CC = gcc $(CFLAGS)
CFLAGS = -Wall -Werror -Wextra -pedantic -std=c99
OBJECTS =  hello.o cat.o
BINS = hello cat

.PHONY: all
all : $(BINS)

cat.o : cat.c
	$(CC) -c cat.c

cat : cat.o
	$(CC) cat.o -o cat

hello.o : hello.c
	$(CC) -c hello.c

hello : hello.o
	$(CC) hello.o -o hello

.PHONY: clean
clean:
	$(RM) $(OBJECTS) $(BINS)
