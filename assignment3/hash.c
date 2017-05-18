# include "hashFunc.h" // hash function
# include "ll.h"   // linked list interface

typedef struct hashTable
{
	listNode **h;  // Array of pointers to heads of linked lists
	uint32_t s[4]; // Salt
	uint32_t l;    // Length
} hashTable;

uint16_t hashHT(hashTable *, const char *)
{

}

/*
hashTable *newHT(uint32_t, uint32_t []);

void delHT(hashTable *);

listNode *findHT(hashTable *, const char *);

void insertHT(hashTable *, const char *, const char *);
/*
