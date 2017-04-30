# include <stdio.h> // printf, perror
# include <stdlib.h> // atoi, rand & srand, malloc/calloc/realloc/free
# include <getopt.h> // getopt
# include "bv.h"
# include "minsort.h"

enum sortingAlgorithms { MIN, BUBBLE, INSERTION, QUICK, MERGE, END };

void printArray(uint32_t a[], uint32_t printLength);

int main(int argc, char *argv[])
{
	uint32_t printNum = 100, seed = 8222022, capacity = 100, length = 0;
	bitV *sorts = newVec(8);

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

	/*
	* Create a dynamic array of random 24 bit integers.
	*/	

	srand(seed);
	uint32_t *nums = (uint32_t *) calloc(capacity, sizeof(uint32_t));	
	for (uint32_t i = 0; i < capacity; i += 1)
	{
		if (length == capacity)
		{
			// reallocate memory to expand the array
		}
		nums[i] = rand() & MASK;
		length += 1;
	}

	/*
	* Sort the array.
	* Print the array.
	*/

	minSort(nums, length);	
	printArray(nums, printNum);
	
	/*
	* Currently prints out an unsorted array of 24 bit integers
	* Next: sort the array with minsort and reallocate memory to expand array
	* After: sort the array with any algorithm(s) requested by flags
	*/

	printf("\n");

	return 0;
}

void printArray(uint32_t a[], uint32_t length)
{
	for (uint32_t i = 0; i < length; i += 1)
	{
		int columnWidth = 8;
		printf("  %*d", columnWidth, a[i]);

		if ((i+1) % 7 == 0) // print a new line after every 7 entries
		{
			printf("\n");
		}
	}
}
