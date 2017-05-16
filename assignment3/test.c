# include <stdio.h>
# include "bf.h"   // Bloom Filters
# include "hash.h" // hash function, takes in a salt[4] and a *key

int main(void)
{
	uint32_t initA[] = {0xDeadD00d, 0xFadedBee, 0xBadAb0de, 0xC0c0aB0a}; // four salts for the first BF
	bloomF *filter = newBF(8, initA); // new bloom filter of 8 bits with initA hashes as salts
	const char *keys[10] = { "fucking nerd", "darrell is amazing", "test key", "unixislove", "plsnoticemesenpai",
				 "test string",  "a",                  "ab",       "abc",        "abc"             };

	for (int i = 0; i < 10; i++)
	{
		printf("%u\n", hash(filter->s, keys[i]));
	}

	return 0;
}
