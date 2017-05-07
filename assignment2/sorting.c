# include <stdio.h>      // printf, perror
# include <stdlib.h>     // atoi, rand & srand, malloc/calloc/realloc/free
# include <getopt.h>     // getopt
# include <errno.h>      // errno
# include "bv.h"         // bitVectors
# include "minsort.h"    // minsort
# include "bubblesort.h" // bubblesort
# include "insertionsort.h" // insertionsort

enum sortingAlgorithms { UNSORTED, MIN, BUBBLE, INSERTION, QUICK, MERGE, END };

void randomizeArray(uint32_t a[], uint32_t len, uint32_t seed);
void sortArray(uint32_t a[], uint32_t len, uint8_t sortType, uint8_t printFlag, uint32_t printLen);
void printArray(uint32_t a[], uint32_t len, uint32_t printLen, uint32_t moves, uint32_t compares);

int main(int argc, char *argv[])
{
	uint32_t printNum = 100, seed = 8062022, capacity = 100;
	bitV *sortFlags = newVec(7);

	int opt;
	while ((opt = getopt(argc, argv, "AumbiqMp:r:n:")) != -1)
	{
		switch (opt)
		{
			case 'A':
			{
				oneVec(sortFlags);
				break;
			}
			case 'u':
			{
				setBit(sortFlags, UNSORTED);
				break;
			}
			case 'm':
			{
				setBit(sortFlags, MIN);
				break;
			}
			case 'b':
			{
				setBit(sortFlags, BUBBLE);
				break;
			}
			case 'i':
			{
				setBit(sortFlags, INSERTION);
				break;
			}
			case 'q':
			{
				setBit(sortFlags, QUICK);
				break;
			}
			case 'M':
			{
				setBit(sortFlags, MERGE);
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

	uint32_t *nums = (uint32_t *) malloc(capacity * sizeof(uint32_t));
	if (nums == NULL)
	{
		printf("Malloc error {nums == NULL) [%d]", errno);
		return errno;
	}

	uint8_t currentSort = UNSORTED;
	while (currentSort != END)
	{
		if (valBit(sortFlags, currentSort))
		{
			randomizeArray(nums, capacity, seed);
			sortArray(nums, capacity, currentSort, 1, printNum);
		}
		currentSort += 1;
	}

	delVec(sortFlags);
	free(nums);
	nums = NULL;

	return 0;
}

void randomizeArray(uint32_t a[], uint32_t len, uint32_t seed)
{
	srand(seed);
	for (uint32_t i = 0; i < len; i += 1)
	{
		a[i] = rand() & MASK;
	}
}

void sortArray(uint32_t a[], uint32_t len, uint8_t sortType, uint8_t printFlag, uint32_t printLen)
{
	switch (sortType)
	{
		case UNSORTED:
		{
			uint32_t moveCount = 0;
			uint32_t compareCount = 0;
			if (printFlag)
			{
				printf("Unsorted\n");
				printArray(a, len, printLen, moveCount, compareCount);
			}
			break;
		}
		case MIN:
		{
			uint32_t moveCount = 0;
			uint32_t compareCount = 0;
			minSort(a, len, &moveCount, &compareCount);
			if (printFlag)
			{
				printf("Min Sort\n");
				printArray(a, len, printLen, moveCount, compareCount);
			}
			break;
		}
		case BUBBLE:
		{
			uint32_t moveCount = 0;
			uint32_t compareCount = 0;
			bubbleSort(a, len, &moveCount, &compareCount);
			if (printFlag)
			{
				printf("Bubble Sort\n");
				printArray(a, len, printLen, moveCount, compareCount);
			}
			break;
		}
		case INSERTION:
		{
			uint32_t moveCount = 0;
			uint32_t compareCount = 0;
			insertionSort(a, len, &moveCount, &compareCount);
			if (printFlag)
			{
				printf("Insertion Sort\n");
				printArray(a, len, printLen, moveCount, compareCount);
			}
			break;
		}
		case QUICK:
		{

			break;
		}
		case MERGE:
		{

			break;
		}
	}
}

/*
 * printArray: prints each number in a[] up to a printAmount or len of the array
 *	to print all elements of the array, make printAmount = length
 *
 * @param   a            The array of integers to print
 * @param   len          The number of elements in the array
 * @param   printLen  The number of elements to print
 * @return  void
 */
void printArray(uint32_t a[], uint32_t len, uint32_t printLen, uint32_t moves, uint32_t compares)
{
	printf("%u elements\n", len);
	printf("%u moves\n", moves);
	printf("%u compares\n", compares);
	for (uint32_t i = 0; i < printLen && i < len; i += 1)
	{
		int columnWidth = 8;
		printf("  %*u", columnWidth, a[i]);

		if ((i+1) % 7 == 0) // print a new line after every 7 entries
		{
			printf("\n");
		}
	}
	printf("\n");
}

