#include <math.h>
#include "sieve.h"

void sieve(bitV *v) // Sieve of Eratosthenes
{
	oneVec(v); // Assume all are prime
	clrBit(v, 0); // 0 is 0
	clrBit(v, 1); // 1 is unity
	setBit(v, 2); // 2 is prime
	for (uint32_t i = 2; i <= sqrtl(lenVec(v)); i += 1) // check up to sqrt(n)
	{
		if (valBit(v, i)) // if the number is prime
		{
			for (uint32_t k = 0; (k + i) * i <= lenVec(v); k += 1)
			{
				clrBit(v, (k + i) * i);
			}
		}
	}
}

