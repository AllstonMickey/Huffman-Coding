# include <stdint.h>
# define SWAP(x, y) { uint32_t t = x; x = y; y = t; ; }

/*
 * partition: modifies an array so that values to the left of a chosen pivot
 * 	are smaller than the pivot, and values to the right are larger.
 */
uint32_t partition(uint32_t a[], uint32_t length)
{
	uint32_t pivot = a[0];
	uint32_t left = 1;
	uint32_t right = length - 1;

	/*
	 * increment the left index until a value must be swapped.
	 * decrement the right index until a value must be swapped.
	 * when both values must be swapped, swap them if the two
	 * indeces have not crossed each other.
	 */
	uint8_t partitioned = 0;
	while (!partitioned)
	{
		
		while (a[left] <= pivot)
		{
			left += 1;
		}
		while (a[right] > pivot)
		{
			right -= 1;
		}
		if (left < right)
		{
			SWAP(a[left], a[right]);
		}
		else
		{
			partitioned = 1;
		}
	}
	SWAP(a[0], a[right]);
	return right;
}

/*
 * quickSort: recursively sort an array through partitioning until 1 element.
 * 	By joining all partitioned arrays together, the main array is sorted.
 */
void quickSort(uint32_t a[], uint32_t length)
{
	if (length == 0 || length == 1)
	{
		return;
	}
	
	uint32_t pivot = partition(a, length);

	uint32_t *left;
	left = a;
	uint32_t leftLength = pivot;
	quickSort(left, leftLength);

	uint32_t *right;
	right = a + pivot + 1;
	uint32_t rightLength = length - pivot - 1;
	quickSort(right, rightLength);
}

