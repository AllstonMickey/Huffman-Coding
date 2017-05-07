/*
 * minsort.h
 * Author: Darrell Long
 * CMPS 12B: Spring 2017
 */

# ifndef _MINSORT_H
# define _MINSORT_H
# include <stdint.h>

// minIndex: find the index of the least element.
uint32_t minIndex(uint32_t a[], uint32_t first, uint32_t last, uint32_t *compares);

// minSort: sort by repeatedly finding the least element;
void minSort(uint32_t a[], uint32_t length, uint32_t *moves, uint32_t *compares);

# endif
