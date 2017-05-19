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
		ht->h = (listNode **) calloc(len, sizeof(listNode *));
		
		/*
		 * Do not need to allocate *(ht->h) right now because it
		 * will be allocated when calling newNode().
		 */

		ht->l    = len;
		ht->s[0] = hashes[0];
		ht->s[1] = hashes[1];
		ht->s[2] = hashes[2];
		ht->s[3] = hashes[3];
	}
	return ht;
}

/*
 * Deletes a Hash Table and its linked lists (if any).
 *
 * @param ht Hash Table to delete
 * @return void
 */
void delHT(hashTable *ht)
{
	for (uint32_t i = 0; i < ht->l; i += 1)
	{
		if (ht->h[i] != NIL)
		{
			delLL(ht->h[i]);
		}
	}

	free(ht->h);
	ht->h = NIL;
	
	free(ht);
	ht = NIL;
}

/*
   listNode *findHT(hashTable *ht, const char *key)
   {

   }
   */

void insertHT(hashTable *ht, const char *word, const char *tran)
{
	uint16_t index = hashHT(ht, word);
	ht->h[index] = newNode(word, tran);
}

/*
 * For each index of the Hash Table, print its linked list.
 */
void printHT(const hashTable *ht)
{
	printf("\n######## Printing Hash Table ########\n");
	for (uint32_t i = 0; i < ht->l; i += 1) // for each byte
	{
		if (ht->h[i] != NIL)
		{
			printf("%u:\n", i);
			printLL(ht->h[i]); // print the list starting from the head at the ith index
		}
	}
}

