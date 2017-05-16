# include <stdio.h>
# include "bf.h"   // Bloom Filters
# include <math.h>  // pow

int main(void)
{
	uint32_t initA[] = {0xDeadD00d, 0xFadedBee, 0xBadAb0de, 0xC0c0aB0a}; // four salts for the first BF
	bloomF *filter = newBF(65506, initA); // new bloom filter of 65k entries with initA hashes as salts
	const char *keys[5] = { "fucking nerd", "darrell is amazing", "test key", "unixislove", "test key" };
	
	for (int i = 0; i < 5; i++)
	{
		setBF(filter, keys[i]);
		printf(" %u", valBF(filter, hash(filter->s, keys[i]) % 16));
	}
	
	printf("\n");
	return 0;
}
