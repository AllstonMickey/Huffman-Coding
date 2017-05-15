# ifndef NIL
# define NIL (void *) 0
# endif
# ifndef _BF_H
# define _BF_H
# include <stdint.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct bloomF
{
	uint8_t *v; // Vector
	uint32_t l; // Length
	uint32_t s[4]; // Salt
} bloomF;

// Each function has its own has function, determined by the salt.

uint32_t hashBF(bloomF *, char *);

/*
 * Create a new Bloom Filter
 *
 * @param len     Length, number of bits
 * @param hashes  Hash functions
 *
 * @return bloomF The new BF
 */
static inline bloomF *newBF(uint32_t len, uint32_t hashes[])
{
	bloomF *bf = (bloomF *) malloc(sizeof(bloomF));
	if (bf != NIL)
	{
		bf->v = (uint8_t *) calloc((len / 8) + 1, sizeof(uint8_t));
		if (bf->v != NIL)
		{
			bf->l    = len;
			bf->s[0] = hashes[0];
			bf->s[1] = hashes[1];
			bf->s[2] = hashes[2];
			bf->s[3] = hashes[3];
			printf("%u\n", bf->s[2]);
			printf("%u\n", bf->l);
		}
		else
		{
			perror("calloc error [bf.h:34]: bf->v == NIL\n");
		}
	}
	else
	{
		perror("malloc error [bf.h:31]: bf == NIL\n");
	}
	return bf;
}

/*
 * Deletes a Bloom Filter
 * 
 * @param bf Bloom Filter to delete
 * @return void
 */
static inline void delBF(bloomF *bf)
{
	if (bf != NIL)
	{
		if (bf->v != NIL)
		{
			bf->s[0] = 0;
			bf->s[1] = 0;
			bf->s[2] = 0;
			bf->s[3] = 0;
			bf->l    = 0;
			
			free(bf->v);
			if (bf->v == NIL)
			{
				perror("free error [bf.h:75]: bf->v == NIL\n");
			}
			bf->v = NIL;
		}

		free(bf);
		if (bf == NIL)
		{
			perror("free error [bf.h:82]: bf == NIL\n");
		}
		bf = NIL;
	}
}

// Return the value of position k in the Bloom filter

static inline uint32_t valBF(bloomF *x, uint32_t k)
{
	// Code
}

static inline uint32_t lenBF(bloomF *x)
{
	return x->l;
}

// Count bits in the Bloom filter

static inline uint32_t countBF(bloomF *b)
{
	// Code
}

// Set an entry in the Bloom filter

static inline void setBF(bloomF *x, char *key)
{
	// Code
}

// Clear an entry in the Bloom filter

static inline void clrBF(bloomF *x, char *key)
{
	// Code
}

// Check membership in the Bloom filter

static inline uint32_t memBF(bloomF *x, char *key)
{
	// Code
}

static inline void printBF(bloomF *x)
{
	// Code
}

# endif
