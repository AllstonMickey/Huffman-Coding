# include <stdio.h>   // printf, perror
# include <stdlib.h>  // atoi, rand & srand, malloc/calloc/realloc/free
# include <getopt.h>  // getopt
# include <errno.h>   // errno
# include "bv.h"      // bitVectors
# include "minsort.h" // minsort

enum sortingAlgorithms { UNSORTED, MIN, BUBBLE, INSERTION, QUICK, MERGE, END };

void printArray(uint32_t a[], uint32_t len, uint32_t printAmount);

int main(int argc, char *argv[])
{
	uint32_t printNum = 100, seed = 8062022, capacity = 100, length = 0;
	bitV *sorts = newVec(8);

	int opt;
	while ((opt = getopt(argc, argv, "AmbiqMup:r:n:")) != -1)
	{
		switch (opt)
		{
			case 'A':
			{
				oneVec(sorts);
				break;
			}
			case 'm':
			{
				setBit(sorts, MIN);
				break;
			}
			case 'u':
			{
				setBit(sorts, UNSORTED);
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
				// invalid parameter input?
				// no argument supplied to a parameter that required one?
				break;
			}
			default:
			{
				// something very bad happened, unknown error
				break;
			}
		}
	}

	/*
	 * Create a dynamic array of random 24 bit integers.
	 */	

	srand(seed);
	uint32_t *nums = (uint32_t *) calloc(capacity, sizeof(uint32_t));
	if (nums == NULL)
	{
		printf("Calloc error {nums == NULL) [%d]", errno);
		return errno;
	}

	for (uint32_t i = 0; i < capacity; i += 1)
	{
		nums[i] = rand() & MASK;
		length += 1;
	}
	
	//printArray(nums, length, printNum); // unsorted array (USE FOR TESTING)


	/*
	 * TODO: if the sort flag is true, copy the unsorted array into the specified sort
	 * TODO: count moves and compares per sort
	 */


	/*
	if (valBit(sorts, UNSORTED))
	{
		printArray(nums, length, printNum);
	}
	if (valBit(sorts, MIN))
	{

	}
	if (valBit(sorts, BUBBLE))
	{

	}
	if (valBit(sorts, INSERTION))
	{
		
	}
	if (valBit(sorts, QUICK))
	{

	}
	if (valBit(sorts, MERGE))
	{

	}
	*/
	
	uint8_t currentSort = UNSORTED;
	while (currentSort != END)
	{
		if (valBit(sorts, currentSort))
		{
			if (currentSort == UNSORTED)
			{
				printArray(nums, length, printNum);	
			}	
			else
			{
				// sort
				// print sorted
			}
		}
		currentSort += 1;
	}

	/*
	 * Free all allocated memory:
	 * 	sorts bitVector
	 * 	nums 24-bit int array
	 */
	delVec(sorts);
	free(nums);
	nums = NULL;

	return 0;
}

/*
 * printArray: prints each number in a[] up to a printAmount or len of the array
 *	to print all elements of the array, make printAmount = length
 *
 * @param   a            The array of integers to print
 * @param   len          The number of elements in the array
 * @param   printAmount  The number of elements to print
 * @return  void
 */
void printArray(uint32_t a[], uint32_t len, uint32_t printAmount)
{
	for (uint32_t i = 0; i < printAmount && i < len; i += 1)
	{
		int columnWidth = 8;
		printf("  %*d", columnWidth, a[i]);

		if ((i+1) % 7 == 0) // print a new line after every 7 entries
		{
			printf("\n");
		}
	}
	printf("\n");
}

