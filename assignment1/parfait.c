#include <stdio.h>
#include "sieve.h"
#include <math.h>

void printPr(bitV *v, uint32_t n);
void printPrimeFactors(bitV *v, uint32_t n);
uint32_t isPerfect(bitV *v, uint32_t n);
void printProperDivisors(uint32_t n);

int main(void)
{
	uint32_t l = 8150;
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
			printf("\n");
			if (isPerfect(v, i))
			{
				printf("%d E:", i);
				printProperDivisors(i);
				// ... still should list proper divisors
				printf("\n");
			}
		}

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

uint32_t isPerfect(bitV *v, uint32_t n)
{
	uint32_t perfect = 0;
	if (n % 2 == 0) // only known perfect numbers are even
	{
		for (uint32_t i = 2; i <= n; i++)
		{
			if (valBit(v, i))
			{
				uint32_t perfForm = pow(2, i - 1) * (pow(2, i) - 1);
				if (n == perfForm)
				{
					perfect = 1;
				}
			}
		}
	}
	return perfect;
}

void printProperDivisors(uint32_t n)
{
	for (uint32_t i = 1; i < n; i++)
	{
		if (n % i == 0)
		{
			printf(" %d", i);
		}
	}
}
