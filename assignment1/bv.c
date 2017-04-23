#include "bv.h"
#include <stdlib.h>

bitV *newVec(uint32_t len) // creates a new vector of specified length in bits
{
	bitV *vec = malloc(sizeof(bitV));
	vec->v = calloc(len / 8 + 1, sizeof(uint8_t));
	vec->l = len;
	return vec;
}

void delVec(bitV *vec) // deletes a vector
{
	free(vec->v);
	free(vec);
}

void oneVec(bitV *vec) // sets a vector to all 1
{
	for (uint32_t i = 0; i < (vec->l); i++)
	{
		(vec->v)[i] |= 0xFF;
	}
}

void setBit(bitV *vec, uint32_t bit) // sets a specified bit
{
	(vec->v)[bit >> 3] |= (01 << (bit % 8));
}

void clrBit(bitV *vec, uint32_t bit) // clears a specified bit
{
	(vec->v)[bit >> 3] &= ~(01 << (bit % 8));
}

uint8_t valBit(bitV *vec, uint32_t bit) // returns the value of a specified bit
{
	return ((vec->v)[bit >> 3] & (01 << (bit % 8))) >> (bit % 8);
}

uint32_t lenVec(bitV *vec) // returns the length of the vector
{
	return vec->l;
}

