/* 
 * bf.h - Bloom Filter
 * Interface Author: Galdrafoor
 */

# ifndef NIL
# define NIL (void *) 0
# endif

# ifndef _BF_H
# define _BF_H

# include <stdint.h>
# include <stdlib.h>
# include <stdio.h>
# include "hashFunc.h"

typedef struct bloomF
{
	uint8_t *v; // Vector
	uint32_t l; // Length
	uint32_t s[4]; // Salt
} bloomF;

/*
 * Hashes a key that into a value that is less than the number of bits in the Bloom Filter.
 *
 * @param bf  Bloom Filter which contains the 4 salts for the hash function
 * @param key Key to hash.
 * @return Hashed value of key.
 */
uint32_t hashBF(bloomF *bf, const char *key)
{
	return hash(bf->s, key) % bf->l;
}

/*
 * Create a new Bloom Filter
 *
 * @param len     Length, number of bits to allocate to the new BF
 * @param hashes  Array of hash functions (must be size of 4!)
 * @return bloomF The pointer to the new BF
 */
static inline bloomF *newBF(uint32_t len, uint32_t hashes[])
{
	bloomF *bf = (bloomF *) malloc(sizeof(bloomF));
	if (bf == NIL)
	{
		perror("malloc error [bf.h:39]: bf is NIL\n");
	}
	else
	{
		bf->v = (uint8_t *) calloc((len / 8) + 1, sizeof(uint8_t));
		if (bf->v == NIL)
		{
			perror("calloc error [bf.h:46]: bf->v is NIL\n");
		}
		else
		{
			bf->l    = len;
			bf->s[0] = hashes[0];
			bf->s[1] = hashes[1];
			bf->s[2] = hashes[2];
			bf->s[3] = hashes[3];
		}
	}
	return bf;
}

/*
 * Deletes a Bloom Filter.
 * If there is something of the Bloom Filter in memory to free (not NIL), 
 * free it and set to NIL.
 * 
 * @param bf Bloom Filter to delete
 * @return void
 */
static inline void delBF(bloomF *bf)
{
	free(bf->v);
	bf->v = NIL;
	
	free(bf);
	bf = NIL;
}

/*
 * Returns the value of the kth bit in the Bloom Filter
 *
 * @param bf  Bloom Filter to check
 * @param bit Index of the bit, 0 to (bf->l - 1) inclusive.
 * @return 0: bit is turned off
 *         1: bit is turned on
 */
static inline uint8_t valBF(bloomF *bf, uint32_t bit)
{
	return ((bf->v)[bit >> 3] & (0x1 << (bit % 8))) >> (bit % 8);
}

/*
 * Returns the length of the Bloom Filter
 *
 * @param bf Bloom Filter to check
 * @return Length, number of total bits allocated to the BF
 */
static inline uint32_t lenBF(bloomF *bf)
{
	return bf->l;
}

/*
 * Count bits in the Bloom Filter.
 * For each bit, if it's turned on (1), count it.
 *
 * @param bf Bloom Filter to check
 * @return Number of set bits in BF
 */
static inline uint32_t countBF(bloomF *bf)
{
	uint32_t count = 0;
	for (uint32_t i = 0; i < bf->l; i += 1)
	{
		if (valBF(bf, i))
		{
			count += 1;
		}
	}
	return count;
}

/*
 * Hashes a key string to a 2 byte unsigned integer.
 * Sets the BF vector's bit to 1 in the index of the hashed value.
 *
 * @param bf  Bloom Filter to set bit in
 * @param key String to hash into an index for the BF vector
 * @return void
 */
static inline void setBF(bloomF *bf, const char *key)
{
	uint32_t bit = hashBF(bf, key);
	(bf->v)[bit >> 3] |= (0x1 << (bit % 8));
}

/*
 * Hashes a key string to a 2 byte unsigned integer.
 * Clears the BF vector's bit to 0 in the index of the hased value.
 *
 * @param bf  Bloom Filter to clear bit in
 * @param key String to hash into an index for the BF vector
 * @return void
 */
static inline void clrBF(bloomF *bf, const char *key)
{
	uint32_t bit = hashBF(bf, key);
	bf->v[bit >> 3] &= ~(0x1 << (bit % 8));
}

/*
 * Check membership in the Bloom Filter by hashing the key
 * and returning the value of its bit.
 *
 * @param bf  Bloom Filter to check
 * @param key Key to check
 * @return 0: bit is turned off
 *         1: bit is turned on
 */
static inline uint8_t memBF(bloomF *bf, const char *key)
{
	uint32_t bit = hashBF(bf, key);
	return valBF(bf, bit);
}

/*
 * Prints values of bits in BF with
 *   - 3 bytes per new line
 *   - 4 bit separations
 *
 * @param bf Bloom Filter to print
 * @return void
 */
static inline void printBF(bloomF *bf)
{
	for (uint32_t i = 0; i < bf->l; i += 1)
	{
		printf("%u", valBF(bf, i));
		if ((i + 1) % 24 == 0)
		{
			printf("\n");
		}
		if (i % 4 == 0)
		{
			printf(" ");
		}
	}
	printf("\n");
}

# endif
