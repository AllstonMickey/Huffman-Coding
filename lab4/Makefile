CC = gcc
CFLAGS = -Wall -Werror -Wextra -Wpedantic -std=c99 -lpthread
RM = rm -f

.PHONY: all
all : increment

increment : increment.o
	$(CC) $(CFLAGS) increment.o -o increment

increment.o : increment.c
	$(CC) $(CFLAGS) increment.c -c

.PHONY: clean
clean:
	$(RM) increment.o increment
