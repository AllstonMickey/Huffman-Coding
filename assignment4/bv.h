/*
 * Interface provided by Darrell Long
 * Course: CMPS 12B Spring 2017
 */

# ifndef _BVector
# define _BVector
# include <stdint.h>
# include <stdlib.h> // malloc, calloc, free
# include <stdio.h>  // printf

# ifndef NIL
# define NIL (void *) 0
# endif

typedef struct bitV {
	uint8_t *v;
	uint64_t l;
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
	for (uint32_t i = 0; i < (vec->l) / 8 + 1; i += 1)
	{
		(vec->v)[i] |= 0xFF;
	}
}

static inline void setBit(bitV *vec, uint64_t b)
{
	(vec->v)[b >> 3] |= (0x1 << (b % 8));
}

static inline void clrBit(bitV *vec, uint64_t b)
{
	(vec->v)[b >> 3] &= ~(0x1 << (b % 8));
}

static inline uint8_t valBit(bitV *vec, uint64_t b)
{
	return ((vec->v)[b >> 3] & (0x1 << (b % 8))) >> (b % 8);
}

static inline uint32_t lenVec(bitV *vec)
{
	return vec->l;
}

static inline void printVec(bitV *vec)
{
	for (uint32_t i = 0; i < (vec->l); i += 1)
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
