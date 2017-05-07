# include "bubblesort.h"
# define SWAP(x, y) { uint32_t t = x; x = y; y = t; ; }

void bubbleSort(uint32_t a[], uint32_t length, uint32_t *moves, uint32_t *compares)
{
	uint8_t swapped = 1;
	uint32_t n = length; // n: the length of the array that must be checked for pairs
	while (swapped)
	{
		swapped = 0;
		for (uint32_t i = 1; i < n; i += 1)
		{
			*compares += 1;
			if (a[i-1] > a[i])
			{
				SWAP(a[i-1], a[i]);
				*moves += 3;
				swapped = 1;
			}
		}
		n -= 1;
	}
}

