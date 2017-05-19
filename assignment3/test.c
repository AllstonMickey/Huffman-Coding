# include <stdio.h> // printing
# include "bf.h"    // Bloom Filters
# include <math.h>  // pow
# include "hash.h"  // hash tables & linked lists

bool moveToFront;

int main(void)
{
	const char *keys[5] = { "fucking nerd",  "darrell is amazing", "test key", "windowsIsLove", "redditors" };
	const char *tran[5] = { "jimmy neutron", "darrell is Odin",    "test key", "unixIsLife",    "poltards"  };
	uint8_t keyLen = 5;
	uint32_t entries = pow(2, 2);

	printf("----------- FIRST SALT STARTING -------------\n");

	uint32_t initA[] = {0xDeadD00d, 0xFadedBee, 0xBadAb0de, 0xC0c0aB0a}; // first set of salts
	bloomF *a = newBF(entries, initA); // new bloom filter of 65k entries with initA hashes as salts
	for (int i = 0; i < keyLen; i += 1)
	{
		printf("%u %s\n", hashBF(a, keys[i]), keys[i]);
		setBF(a, keys[i]);
	}

	printf("\n\n--------- SECOND SALT STARTING ----------\n");
	uint32_t initB[] = {0xDeadBeef, 0xFadedB0a, 0xCafeD00d, 0xC0c0aB0a}; // second set of salts
	bloomF *b = newBF(entries, initB);
	for (int i = 0; i < keyLen; i += 1)
	{
		printf("%u %s\n", hashBF(b, keys[i]), keys[i]);
		setBF(b, keys[i]);
	}

	delBF(a);
	delBF(b);

	// TODO: this broke for some reason?	
	moveToFront = true;

	/*
	uint32_t initH[] = {0xDeadD00d, 0xFadedBee, 0xBadAb0de, 0xC0c0Babe}; // salts for hash table
	hashTable *table = newHT(entries, initH);
	
	printf("\n\n---------- THIRD SALT STARTING ----------\n");
	for (int i = 0; i < keyLen; i += 1)
	{
		printf("%u %s\n", hashHT(table, keys[i]), keys[i]);
		insertHT(table, keys[i], tran[i]);
	}
	
	printHT(table);
	findHT(table, keys[3]);
	printHT(table);
	delHT(table);
	*/

	
	listNode *head1 = newNode(keys[0], tran[0]);

	listNode *head2 = newNode(keys[4], tran[4]);
	listNode *third = newNode(keys[3], tran[3]);
	head2->next = third;
	listNode *first = newNode(keys[1], tran[1]);
	third->next = first;

	listNode *head3 = newNode(keys[2], tran[2]);
	
	printf("---- new ----\n"); printLL(head1); printf("\n"); printLL(head2); printf("\n"); printLL(head3);
	findLL(&head2, keys[3]);
	printf("\n---- new ----\n"); printLL(head1); printf("\n"); printLL(head2); printf("\n"); printLL(head3);
	return 0;
}
