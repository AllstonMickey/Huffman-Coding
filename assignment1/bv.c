#include <stdio.h>
#include "bv.h"
#include <stdlib.h>

bitV *newVec(uint32_t len) // creates a new vector of specified length
{
	bitV *v = calloc(len, 1);
	return v;
}

void delVec(bitV *v) // deletes a vector
{
	free(v);
}

void one(bitV *v) // sets a vector to all 1
{
	for (int i = 0; i < (v->l); i++) // for the length of the bit vector
	{
		v[i] |= 11111111;
	}
}

void setBit(bitV *v, uint32_t bit) // sets a specified bit
{
	v[bit >> 3] |= (01 << (bit & 07));
}

void clrBit(bitV *v, uint32_t bit) // clears a specified bit
{
	v[bit >> 3] &= ~(01 << (bit & 07));
}

uint8_t valBit(bitV *v, uint32_t bit) // returns the value of a specified bit
{
	return (v[bit >> 3] & (01 << (bit & 07))) >> (bit & 07);
}

uint32_t lenVec(bitV *v) // returns the length of the vector
{
	return v->l;
}
