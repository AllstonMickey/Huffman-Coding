# include <stdio.h>         // printf, perror
# include <stdlib.h>        // atoi, rand & srand, malloc/calloc/realloc/free
# include <getopt.h>        // getopt
# include <errno.h>         // errno
# include "bv.h"            // bitVectors
# include "minsort.h"       // minsort
# include "bubblesort.h"    // bubblesort
# include "insertionsort.h" // insertionsort
# include "quicksort.h"     // quicksort

enum sortingAlgorithms { UNSORTED, MIN, BUBBLE, INSERTION, QUICK, MERGE, END };

void randomizeArray(uint32_t a[], uint32_t len, uint32_t seed); // fills all array elements with random 24 bit numbers
void sortArray(uint32_t a[], uint32_t len, uint8_t sortType, uint8_t printFlag, uint32_t printLen); // sorts an array by algorithm
void printArray(uint32_t a[], uint32_t len, uint32_t printLen, uint32_t moves, uint32_t compares); // prints an array up to n

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
				clrBit(sortFlags, UNSORTED); // to mimic Darrell's -A option
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

/*
 * randomizeArray: sets all array elements to a random 24-bit natural number.
 * 
 * @param a    The array to randomize.
 * @param len  Length of the array, a.
 * @param seed The rand() seed to set with srand().
 */
void randomizeArray(uint32_t a[], uint32_t len, uint32_t seed)
{
	srand(seed);
	for (uint32_t i = 0; i < len; i += 1)
	{
		a[i] = rand() & MASK;
	}
}

/*
 * sortArray: sorts an array of length by a specified sorting algorithm.  Also prints if requested.
 *
 * @param a         The array to sort.
 * @param len       Length of the array, a.
 * @param sortType  The sorting algorithm to use.  Definitions are in the enum "sortingAlgorithms" at the top of this file.
 * @param printFlag If '0', the array will not be printed after sorting.
 * @param printLen  Only matters if printFlag is set to '1'.  Determines how many elements of the array to print.
 * @return void
 */
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
			uint32_t moveCount = 0;
			uint32_t compareCount = 0;
			quickSort(a, len, &moveCount, &compareCount);
			if (printFlag)
			{
				printf("Quick Sort\n");
				printArray(a, len, printLen, moveCount, compareCount);
			}
			break;
		}
		case MERGE:
		{
			uint32_t moveCount = 0;
			uint32_t compareCount = 0;
			// sort it
			if (printFlag)
			{
				printf("Merge Sort\n");
				printArray(a, len, printLen, moveCount, compareCount);
			}
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

