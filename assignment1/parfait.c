#include <stdio.h>
#include "sieve.h"
#include <math.h>

void printPr(bitV *v, uint32_t n);

void printPrimeFactors(bitV *v, uint32_t n)
{
	for (uint32_t i = 2; i <= n; i++)
	{
		while (valBit(v, i) && (n % i == 0))
		{
			n /= i;
			printf(" %d", i);
		}
	}
}

int main(void)
{
	uint32_t l = 100;
	bitV *v = newVec(l);
	sieve(v);
	for (uint32_t i = 2; i <= l; i++) // go through each 1 < n < 100,001 (i = 2; i <= l)
	{
		if (valBit(v, i)) // prime
		{
			printf("%d P\n", i);
		}
		else // composite
		{
			printf("%d C:", i);
			printPrimeFactors(v, i);
			//printPr(v, i);
			printf("\n");
		}

		// ... still should check for perfect numbers
	}
	return 0;
}

void printPr(bitV *v, uint32_t n)
{
	if (valBit(v, n))
	{
		printf(" %d", n);
	}
	else
	{
		for (uint32_t i = 2; i <= n; i++)
		{
			if (valBit(v, i) && n % i == 0)
			{
				printf(" %d", i);
				printPr(v, n / i);
			}
		}
	}
}

