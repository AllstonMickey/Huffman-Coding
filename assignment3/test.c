# include <stdio.h> // printing
# include "bf.h"    // Bloom Filters
# include <math.h>  // pow

int main(void)
{
	const char *keys[5] = { "fucking nerd", "darrell is amazing", "test key", "unixislove", "test key" };
	uint8_t keyLen = 5;
	
	printf("----------- FIRST SALT STARTING -------------\n");

	uint32_t initA[] = {0xDeadD00d, 0xFadedBee, 0xBadAb0de, 0xC0c0aB0a}; // first set of salts
	bloomF *a = newBF(pow(2, 16), initA); // new bloom filter of 65k entries with initA hashes as salts

	// set BF(a) - hashes the keys into indeces and turns on those indeces
	// print the hash values
	// print the BF
	// make sure they match
	for (int i = 0; i < keyLen; i += 1)
	{
		printf("%u\n", hash(a->s, keys[i]) & MASK);
		setBF(a, keys[i]);
	}
	printBF(a);

	printf("\n\n--------- SECOND SALT STARTING ----------\n");

	// set BF(b) - hashes the keys into indeces and turns on those indeces
	// print the hash values (should be different than part 1)
	// print the BF
	// make sure they match

	uint32_t initB[] = {0xDeadBeef, 0xFadedB0a, 0xCafeD00d, 0xC0c0aB0a}; // second set of salts
	bloomF *b = newBF(pow(2, 16), initB);
	for (int i = 0; i < keyLen; i += 1)
	{
		printf("%u\n", hash(b->s, keys[i]) & MASK);
		setBF(b, keys[i]);
	}
	printBF(b);

	// if still on, it's found
	printf("\n");
	return 0;
}
