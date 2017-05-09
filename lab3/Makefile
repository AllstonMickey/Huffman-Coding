CC = gcc
RM = rm -f
CFLAGS = -Wall -Werror -Wextra -Wpedantic -std=c99 -g -lm

.PHONY: all
all : gdbLab

gdbLab : gdbLab.o
	$(CC) $(CFLAGS) gdbLab.o -o gdbLab

gdbLab.o : gdbLab.c
	$(CC) $(CFLAGS) gdbLab.c -c

.PHONY: clean
clean :
	$(RM) gdbLab.o gdbLab
