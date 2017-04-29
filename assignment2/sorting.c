# include <stdio.h> // printf, perror
# include <stdlib.h> // atoi, rand & srand, malloc/calloc/realloc/free
# include <getopt.h> // getopt
# include "bv.h"
# include "minsort.h"

enum sortingAlgorithms { MIN, BUBBLE, INSERTION, QUICK, MERGE, END };

int main(int argc, char *argv[])
{
	int printNum = 100, seed = 8222022, capacity = 100, length = 0;
	bitV *sorts = newVec(6);

	int opt;
	while ((opt = getopt(argc, argv, "AmbiqMp:r:n:")) != -1)
	{
		switch (opt)
		{
			case 'm':
			{
				setBit(sorts, MIN);
				break;
			}
			case 'p':
			{
				printNum = atoi(optarg);
				break;
			}
			case 'r':
			{
				seed = atoi(optarg);
				break;
			}
			case 'n':
			{
				capacity = atoi(optarg);
				break;
			}
			case '?':
			{
				break;
			}
			default:
			{
				break;
			}
		}
	}
	
	srand(seed);
	uint32_t *nums = (uint32_t *) calloc(capacity, sizeof(uint32_t));	
	for (int i = 0; i < capacity; ++i)
	{
		if (length == capacity)
		{
			// reallocate memory to expand the array
		}
		nums[i] = rand() & MASK;
		length += 1;
	}

	for (int i = 1; i <= printNum; ++i)
	{
		int columnWidth = 8;
		printf("  %*d", columnWidth, nums[i-1]);
		if (i % 7 == 0)
		{
			printf("\n");
		}
	}

	/*
	* Currently prints out an unsorted array of 24 bit integers
	* Next: sort the array with minsort and reallocate memory to expand array
	* After: sort the array with any algorithm(s) requested by flags
	*/

	printf("\n");

	return 0;
}

