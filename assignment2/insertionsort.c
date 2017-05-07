# include "insertionsort.h"
# include <stdio.h>
# define SWAP(x, y) { uint32_t t = x; x = y; y = t; ; }

void insert(uint32_t b[], uint32_t length, uint32_t *moves, uint32_t *compares)
{
	uint32_t num = b[length - 1];
	*moves += 1;

	int32_t i;
	for (i = length - 1; num < b[i-1]; i -= 1)
	{
		b[i] = b[i-1];
		*compares += 1;
		*moves += 1;
	}
	b[i] = num;
	*moves += 1;
}

void insertionSort(uint32_t a[], uint32_t length, uint32_t *moves, uint32_t *compares)
{
	for (uint32_t i = 1; i < length; i += 1)
	{
		insert(a, i + 1, moves, compares);
	}
}

