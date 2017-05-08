# include "quicksort.h"
# define SWAP(x, y) { uint32_t t = x; x = y; y = t; ; }

/*
 * partition: modifies an array so that values to the left of a chosen pivot
 * 	are smaller than or equal to the pivot, and values to the right are larger.
 *
 * @return right The right index and the start of the new pivot within the partitioned array.
 * 		   This index separates the left subarray and the right subarray.
 */
uint32_t partition(uint32_t a[], uint32_t length, uint32_t *moves, uint32_t *compares)
{
	uint32_t pivot = a[0]; // choose the first value as the pivot
	uint32_t left = 1;
	uint32_t right = length - 1;
	uint8_t partitioned = 0;

	/*
 	 * 1. Increment the left index until a value needs to be swapped.
 	 * 2. Decrement the right index until a value needs to be swapped.
 	 * 3. Swap the two values if not done partitioning.
 	 * 4. Otherwise, done partitioning, set the new pivot.
 	 */
	while (!partitioned)
	{
		while ((left < right) && (a[left] <= pivot)) // prevents segfaults if left goes out of length
		{
			left += 1;
			*compares += 1;
		}
		while (a[right] > pivot)
		{
			right -= 1;
			*compares += 1;
		}
		if (left < right)
		{
			SWAP(a[left], a[right]);
			left += 1;
			right -= 1;
			*moves += 3;
		}
		else
		{
			partitioned = 1;
		}
	}
	SWAP(a[0], a[right]);
	*moves += 3;
	return right;
}

/*
 * quickSort: recursively sort an array through partitioning until 1 element.
 * 	By joining all partitioned arrays together, the main array is sorted.
 */
void quickSort(uint32_t a[], uint32_t length, uint32_t *moves, uint32_t *compares)
{
	if (length == 0 || length == 1)
	{
		return;
	}

	uint32_t pivot = partition(a, length, moves, compares);

	uint32_t *left;
	left = a;
	uint32_t leftLength = pivot;
	quickSort(left, leftLength, moves, compares);
	
	uint32_t *right;
	right = a + pivot + 1;
	uint32_t rightLength = length - pivot - 1;
	quickSort(right, rightLength, moves, compares);
}

