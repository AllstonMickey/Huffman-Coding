#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <math.h>
#include "sieve.h"

void printPrimeFactors(bitV *v, uint32_t n);
uint32_t isPerfect(bitV *v, uint32_t n);
void printProperDivisors(uint32_t n);

int main(int argc, char *argv[])
{
	uint32_t l;
	int opt;
	while ((opt = getopt(argc, argv, "n:")) != -1)
	{
		switch (opt)
		{
			case 'n':
			{
				l = atoi(optarg);
				break;
			}
		}
	}

	bitV *v = newVec(l);
	sieve(v);
	for (uint32_t i = 2; i <= l; i++) // go through each bit in the vector
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
				printf("\n");
			}
		}

	}
	delVec(v);
	return 0;
}

void printPrimeFactors(bitV *v, uint32_t n)
{
	for (uint32_t i = 2; i <= n; i++)
	{
		while (valBit(v, i) && (n % i == 0)) // while i is prime and divides evenly into n
		{
			n /= i; // divide n by i
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

