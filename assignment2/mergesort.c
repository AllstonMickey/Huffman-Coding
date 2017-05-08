# include "mergesort.h"
# include <stdlib.h>

/*
 * merge: merges two sorted arrays into one sorted array by comparing the lth and rth
 * 	  element of each array and putting the least one in the ith element of a[].
 *
 * @param a           The merged sorted array
 * @param left        A sorted array to merge
 * @param right       A sorted array to me
 * @param length      The length of the merged sorted array
 * @param leftLength  The length of the left array
 * @param rightLength The length of the right array
 * @return void
 */
void merge(uint32_t a[], uint32_t left[], uint32_t right[],
        uint32_t length, uint32_t leftLength, uint32_t rightLength, uint32_t *moves, uint32_t *compares)
{
	uint32_t l = 0; // current index of left[]
	uint32_t r = 0; // current index of right[]
	for (uint32_t i = 0; i < length; i += 1)
	{
		// case 1: both arrays have elements
		if (l < leftLength && r < rightLength)
		{
			// case 1a: the left has the least element
			if (left[l] < right[r])
			{
				a[i] = left[l];
				l += 1;
			}
			// case 1b: the right has the least element
			else
			{
				a[i] = right[r];
				r += 1;
			}
			*compares += 1;
		}
		// case 2: only the left array has elements
		else if (l < leftLength)
		{
			a[i] = left[l];
			l += 1;
		}
		// case 3: only the right array has elements
		else
		{
			a[i] = right[r];
			r += 1;
		}
		*moves += 1;
	}
}

void mergeSort(uint32_t a[], uint32_t length, uint32_t *moves, uint32_t *compares)
{
	if (length > 1)
	{
		uint32_t leftLength = length/2;
		uint32_t *left = (uint32_t *) malloc(leftLength * sizeof(uint32_t));
		for (uint32_t i = 0; i < leftLength; i += 1)
		{
			left[i] = a[i];
			*moves += 1;
		}

		uint32_t rightLength = length - leftLength;
		uint32_t *right = (uint32_t *) malloc(rightLength * sizeof(uint32_t));
		uint32_t *temp = a + leftLength;
		for (uint32_t i = 0; i < rightLength; i += 1)
		{
			right[i] = temp[i];
			*moves += 1;
		}

		mergeSort(left, leftLength, moves, compares);
		mergeSort(right, rightLength, moves, compares);
		merge(a, left, right, length, leftLength, rightLength, moves, compares);

		free(left);
		free(right);
		left = NULL;
		right = NULL;
	}
	else
	{
		return;
	}
}

