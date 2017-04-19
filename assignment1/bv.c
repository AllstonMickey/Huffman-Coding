#include <stdio.h>
#include "bv.h"
#include <stdlib.h>

bitV *newVec(uint32_t len) // creates a new vector of specified length in bytes
{
	bitV *v = calloc(len, 1);
	return v;
}

void delVec(bitV *vec) // deletes a vector
{
	free(vec);
}

void oneVec(bitV *vec) // sets a vector to all 1
{
	for (uint8_t i = 0; i < (vec->l); i++) // for the length of the bit vector
	{
		(vec->v)[i] |= 11111111;
	}
}

void setBit(bitV *vec, uint32_t bit) // sets a specified bit
{
	(vec->v)[bit >> 3] |= (01 << (bit & 07));
}

void clrBit(bitV *vec, uint32_t bit) // clears a specified bit
{
	(vec->v)[bit >> 3] &= ~(01 << (bit & 07));
}

uint8_t valBit(bitV *vec, uint32_t bit) // returns the value of a specified bit
{
	return ((vec->v)[bit >> 3] & (01 << (bit & 07))) >> (bit & 07);
}

uint32_t lenVec(bitV *vec) // returns the length of the vector
{
	return vec->l;
}
