# ifndef NIL
# define NIL (void *) 0
# endif

# ifndef MASK
# define MASK 0x0000FFFF
# endif

# ifndef _HASH_H
# define _HASH_H

# include <stdint.h>
# include "ll.h"   // linked list interface

typedef struct hashTable
{
	listNode **h;  // Array of pointers to heads of linked lists
	uint32_t s[4]; // Salt
	uint32_t l;    // Length
} hashTable;

uint16_t hashHT(hashTable *ht, const char *key);

hashTable *newHT(uint32_t len, uint32_t hashes[]);

void delHT(hashTable *ht);

listNode *findHT(hashTable *ht, const char *key);

void insertHT(hashTable *ht, const char *word, const char *tran);

void printHT(const hashTable *ht);

# endif
