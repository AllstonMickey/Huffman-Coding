/*
 * Interface provided by Darrell Long
 * Course: CMPS 12B Spring 2017
 */

# ifndef _BVector
# define _BVector
# include <stdlib.h> // malloc, calloc, free
# include <stdio.h>  // printf
# include "code.h"

# ifndef NIL
# define NIL (void *) 0
# endif

# ifndef KB
# define KB 4096
# endif

typedef struct bitV {
	uint8_t *v;
	uint64_t l;
	uint64_t f; // position to place the next 'inactive' bit
} bitV;

static inline bitV *newVec(uint64_t len)
{
	bitV *vec = (bitV *) malloc(sizeof(bitV));
	if (vec)
	{
		vec->v = (uint8_t *) calloc(len / 8 + 1, sizeof(uint8_t));
		if (vec->v)
		{
			vec->l = len;
			vec->f = 0;
			return vec;
		}
	}
	return (bitV *) 0;
}

static inline void delVec(bitV *vec)
{
	free(vec->v);
	vec->v = NIL;
	free(vec);
	vec = NIL;
}

static inline void oneVec(bitV *vec)
{
	for (uint32_t i = 0; i < (vec->l / 8) + 1; i += 1)
	{
		(vec->v)[i] |= 0xFF;
	}
	vec->f = vec->l;
}

static inline void setBit(bitV *vec, uint64_t b)
{
	(vec->v)[b >> 3] |= (0x1 << (b % 8));
	vec->f = b + 1;
}

static inline void clrBit(bitV *vec, uint64_t b)
{
	(vec->v)[b >> 3] &= ~(0x1 << (b % 8));
	vec->f = b + 1;
}

static inline uint8_t valBit(bitV *vec, uint64_t b)
{
	return ((vec->v)[b >> 3] & (0x1 << (b % 8))) >> (b % 8);
}

static inline bool appendCode(bitV *vec, code *c)
{
	while ((vec->f + c->l) > vec->l)
	{
		uint8_t *tmp = (uint8_t *) realloc(vec->v, vec->l + KB);
		if (tmp)
		{
			uint64_t oldLen = vec->l;
			vec->v = tmp;
			vec->l += KB;
			for (uint64_t i = oldLen; i < vec->l; i += 1)
			{
				(vec->v)[i >> 3] &= ~(0x1 << (i % 8));
			}
		}
		else
		{
			tmp = NIL;
			return false;
		}
	}

	for (uint32_t i = 0; i < c->l; i += 1) // for each bit in the stack
	{
		uint8_t val = (c->bits[i >> 3] & (0x1 << (i % 8))) >> (i % 8);
		if (val)
		{
			setBit(vec, vec->f);
		}
		else
		{
			clrBit(vec, vec->f);
		}
	}
	return true;
}

static inline uint32_t lenVec(bitV *vec)
{
	return vec->l;
}

static inline void printVec(bitV *vec)
{
	for (uint32_t i = 0; i < (vec->f); i += 1)
	{
		printf("%u", valBit(vec, i));
		if ((i + 1) % 4 == 0)
		{
			printf(" ");
		}
		if ((i + 1) % 8 == 0)
		{
			printf("\n");
		}
	}
}

# endif
