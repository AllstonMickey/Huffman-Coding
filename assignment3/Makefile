CC = gcc
#REMEMBER TO ADD -WERROR BACK INTO CFLAGS
CFLAGS = -Wall -Wextra -Wpedantic -std=c99
RM = rm -f
HEADERS = bf.h hashFunc.h aes.h ll.h hash.h
OBJECTS = banhammer.o aes.o ll.o hash.o lex.yy.o

.PHONY: all
all : banhammer

banhammer : $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o banhammer -lfl

banhammer.o : banhammer.c $(HEADERS)
	$(CC) $(CFLAGS) banhammer.c -c

lex.yy.o : lex.yy.c
	$(CC) -Werror -Wpedantic lex.yy.c -c

lex.yy.c : words.l
	flex words.l

test : aes.o ll.o hash.o test.o
	$(CC) $(CFLAGS) aes.o ll.o hash.o test.o -o test

test.o : test.c $(HEADERS)
	$(CC) $(CFLAGS) test.c -c



hash.o : hash.c hash.h hashFunc.h
	$(CC) $(CFLAGS) hash.c -c

aes.o : aes.c aes.h
	$(CC) $(CFLAGS) aes.c -c

ll.o : ll.c ll.h strclone.h
	$(CC) $(CFLAGS) ll.c -c

.PHONY: clean
clean :
	$(RM) banhammer test $(OBJECTS) test.o
