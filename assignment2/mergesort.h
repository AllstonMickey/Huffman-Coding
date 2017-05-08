# ifndef _MERGESORT_H
# define _MERGESORT_H

# include <stdint.h>

/*
 * merge: merges two sorted arrays into one sorted array
 */
void merge(uint32_t a[], uint32_t left[], uint32_t right[],
        uint32_t length, uint32_t leftLength, uint32_t rightLength, uint32_t *moves, uint32_t *compares);

void mergeSort(uint32_t a[], uint32_t length, uint32_t *moves, uint32_t *compares);

# endif
