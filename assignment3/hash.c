# include <stdio.h>  // printing
# include <stdlib.h> // allocs
# include "hash.h"   // hash tables and linked lists
# include "hashFunc.h"

/*
 * Hashes a key into a value that is less than the length of the Hash Table.
 *
 * @param ht  Hash Table which contains the four salts required to hash
 * @param key Key to hash
 * @return Hashed value of key.
 */
uint32_t hashHT(hashTable *ht, const char *key)
{
	return hash(ht->s, key) % ht->l;
}

/*
 * Creates a new Hash Table
 *
 * @param len  Length of HT, number of bits/entries
 * @param hashes An array of 4 uint32_t hashes to be used as salts when hashing keys.
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
 * Finds a key in a Hash Table
 * 
 * @param ht  Hash Table to search in
 * @param key Key to search for
 * @return The Node of the Linked List which contains the key
 * 	       returns (listNode *) NIL on failure.
 */
listNode *findHT(hashTable *ht, const char *key)
{
	uint32_t index = hashHT(ht, key);
	listNode *head = ht->h[index];
	listNode *found = findLL(&head, key);

	if (moveToFront && found)
	{
		ht->h[index] = found;
	}

	return found;
}

/*
 * Inserts a word and its translation into a Hash Table
 *
 * @param ht Hash Table to insert into
 * @param word Key value
 * @param tran Translation of the key value/word
 * @return void
 */
void insertHT(hashTable *ht, const char *word, const char *tran)
{
	uint32_t index = hashHT(ht, word);
	listNode *head = ht->h[index];
	if (head == NIL)
	{
		head = newNode(word, tran);
	}
	else
	{
		head = insertLL(&head, word, tran);
	}
	
	ht->h[index] = head;
}

/*
 * For each index of the Hash Table, print its linked list.
 * 
 * @param ht Hash Table to print
 * @return void
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

