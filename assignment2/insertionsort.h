# ifndef _INSERTIONSORT_H
# define _INSERTIONSORT_H

# include <stdint.h>

/* 
 * insert: inserts an element into a sorted subarray of length
 * 	> the number being inserted must be the b[length] element
 */
void insert(uint32_t b[], uint32_t length, uint32_t *moves, uint32_t *compares);

/*
 * insertionSort: sorts an array of length by inserting elements in the 
 *       correct location in a sorted subarray at the beginning of a[].
 */
void insertionSort(uint32_t a[], uint32_t length, uint32_t *moves, uint32_t *compares);

# endif
