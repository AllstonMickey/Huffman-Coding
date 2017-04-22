#include <stdio.h>
#include "sieve.h"

int main(void)
{
	uint32_t length = 100000;
	bitV *v = newVec(length/8);
	sieve(v);
	for (uint32_t i = 2; i < 100; i++)
	{
		if (valBit(v, i))
		{
			printf("%d P\n", i);
		}
	}
	return 0;
}
