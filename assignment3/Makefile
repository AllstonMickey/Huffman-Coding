CC = gcc
#REMEMBER TO ADD -WERROR BACK INTO CFLAGS
CFLAGS = -Wall -Wextra -Wpedantic -std=c99
RM = rm -f
HEADERS = bf.h hashFunc.h aes.h ll.h
OBJECTS = test.o aes.o ll.o

.PHONY: all
all : test

test : $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o test

test.o : test.c $(HEADERS)
	$(CC) $(CFLAGS) test.c -c

aes.o : aes.c aes.h
	$(CC) $(CFLAGS) aes.c -c

ll.o : ll.c ll.h strclone.h
	$(CC) $(CFLAGS) ll.c -c

.PHONY: clean
clean :
	$(RM) test $(OBJECTS)
