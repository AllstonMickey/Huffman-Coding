# ifndef _QUICKSORT_H
# define _QUICKSORT_H

# include <stdint.h>

/*
 * partition: modifies an array so that values to the left of a chosen pivot
 * 	are smaller than the pivot, and values to the right are larger.
 */
void partition(uint32_t a[], uint32_t length);

/*
 * quickSort: recursively sort an array through partitioning until 1 element.
 * 	By joining all partitioned arrays together, the main array is sorted.
 */
void quickSort(uint32_t a[], uint32_t length);

# endif
