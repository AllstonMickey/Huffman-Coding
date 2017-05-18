# include <stdio.h> // printing
# include "bf.h"    // Bloom Filters
# include <math.h>  // pow
# include "ll.h"

bool moveToFront;

int main(void)
{
	const char *keys[5] = { "fucking nerd", "darrell is amazing", "test key", "unixislove", "test key" };
	uint8_t keyLen = 5;
	
	printf("----------- FIRST SALT STARTING -------------\n");

	uint32_t initA[] = {0xDeadD00d, 0xFadedBee, 0xBadAb0de, 0xC0c0aB0a}; // first set of salts
	bloomF *a = newBF(pow(2, 16), initA); // new bloom filter of 65k entries with initA hashes as salts
	for (int i = 0; i < keyLen; i += 1)
	{
		printf("%u\n", hashBF(a, keys[i]));
		setBF(a, keys[i]);
	}
	printBF(a);

	printf("\n\n--------- SECOND SALT STARTING ----------\n");
	uint32_t initB[] = {0xDeadBeef, 0xFadedB0a, 0xCafeD00d, 0xC0c0aB0a}; // second set of salts
	bloomF *b = newBF(pow(2, 16), initB);
	for (int i = 0; i < keyLen; i += 1)
	{
		printf("%u\n", hashBF(b, keys[i]));
		setBF(b, keys[i]);
	}
	printBF(b);

	moveToFront = true;
		
	listNode *head = newNode("faggot", "gay");
	listNode *second = newNode("pols", "redditors");
	head->next = second;
	printLL(head);

	listNode *newHead = insertLL(&head, "darrell", "god");
	printLL(newHead);

	char *key = "pols";
	listNode *found = findLL(&newHead, key);	
	if (found != NIL)
	{
		printf("\nfound key!: %s\n", key);
		printf("found address: %p\n", (void *) found);
		if (moveToFront)
		{
			printLL(found);
		}
		else
		{
			printLL(newHead); 
		}
	}
	else
	{
		printf("\nnot found!: %s\n", key);
		printLL(newHead);
	}
	return 0;
}
