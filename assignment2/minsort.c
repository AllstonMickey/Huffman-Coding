/*
 * minsort.c
 * Author: Darrell Long
 * CMPS 12B: Spring 2017
 */

# include "minsort.h"
# define SWAP(x, y) { uint32_t t = x; x = y; y = t; ; }

// minIndex: find the index of the least element.

uint32_t minIndex(uint32_t a[], uint32_t first, uint32_t last, uint32_t *compares)
{
	uint32_t smallest = first;
	for (uint32_t i = first; i < last; i += 1)
	{
		smallest = a[i] < a[smallest] ? i : smallest;
		*compares += 1;
	}
	return smallest;
}

// minSort: sort by repeatedly finding the least element;

void minSort(uint32_t a[], uint32_t length, uint32_t *moves, uint32_t *compares)
{
	for (uint32_t i = 0; i < length - 1; i += 1)
	{
		uint32_t smallest = minIndex(a, i, length, compares);
		if (smallest != i) // It's silly to swap with yourself!
		{
			SWAP(a[smallest], a[i]);
			*moves += 3;
		}
	}
	return;
}

