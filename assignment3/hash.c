# include <stdio.h>  // printing
# include <stdlib.h> // allocs
# include "hash.h"   // hash tables and linked lists
# include "hashFunc.h"

/*
 * Hashes a key into a 16 bit unsigned integer.
 *
 * @param ht  Hash Table which contains the four salts required to hash
 * @param key Key to hash
 * @return Hashed value of key.
 */
uint16_t hashHT(hashTable *ht, const char *key)
{
	return hash(ht->s, key) & MASK;
}

/*
 * Creates a new Hash Table
 *
 * @param len  Length of HT, number of bits/entries
 * @param hashes An array of 4 uin32_t hashes to be used as salts when hashing keys.
 */
hashTable *newHT(uint32_t len, uint32_t hashes[])
{
	hashTable *ht = (hashTable *) malloc(sizeof(hashTable));
	if (ht == NIL)
	{
		perror("malloc error [hash.c:XX]: ht is NIL\n");
	}
	else
	{
		// initialize an array of pointers to NIL
		ht->h = (listNode **) calloc((len / 8) + 1, sizeof(listNode *));
		if (ht->h == NIL)
		{
			perror("calloc error [hash.c:XX]: ht->h is NIL\n");
		}
		else
		{
			/*
			 * not necessary to allocate *(ht->h) right now because
			 * it will be allocated when using newNode for the first time.
		  	 */

			ht->l    = len;
			ht->s[0] = hashes[0];
			ht->s[1] = hashes[1];
			ht->s[2] = hashes[2];
			ht->s[3] = hashes[3];
		}
	}
	return ht;
}

/*
   void delHT(hashTable *ht)
   {

   }

   listNode *findHT(hashTable *ht, const char *key)
   {

   }

   void insertHT(hashTable *ht, const char *word, const char *tran)
   {

   }
   */

/*
 * For each index of the Hash Table, print its linked list.
 */
void printHT(const hashTable *ht)
{
	printf("######## Printing Hash Table ########");
	for (uint32_t i = 0; i < ht->l; i += 1)
	{
		printf("%u:\n", i);
		printLL(*(ht->h));
	}
}

