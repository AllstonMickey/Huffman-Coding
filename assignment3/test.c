# include <stdio.h> // printing
# include "bf.h"    // Bloom Filters
# include <math.h>  // pow

int main(void)
{
	uint32_t initA[] = {0xDeadD00d, 0xFadedBee, 0xBadAb0de, 0xC0c0aB0a}; // first set of salts
	//uint32_t initB[] = {0xDeadBeef, 0xFadedB0a, 0xCafeD00d, 0xC0c0aB0a}; // second set of salts
	bloomF *filter1 = newBF(pow(2, 16), initA); // new bloom filter of 65k entries with initA hashes as salts
	const char *keys[5] = { "fucking nerd", "darrell is amazing", "test key", "unixislove", "test key" };

	for (int i = 0; i < 5; i++)
	{
		printf("%u\n", hash(filter->s, keys[i]) & MASK);
	}
	
	for (int i = 0; i < 5; i++)
	{
		setBF(filter, keys[i]);
		printf(" %u", valBF(filter, hash(filter->s, keys[i]) & MASK));
	}
	
	for (int i = 0; i < 5; i++)
	{
		clrBF(filter, keys[i]);
		printf(" %u", valBF(filter, hash(filter->s, keys[i]) & MASK));
	}
	printf("\n");
	printBF(filter);

	printf("\n");
	return 0;
}
