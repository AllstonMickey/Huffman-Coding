# ifndef NIL
# define NIL (void *) 0
# endif

# ifndef _HASH_H
# define _HASH_H

# include <stdint.h>
# include <string.h>
# include "aes.h"

/*
 * Author: Darrell Long
 * Course: CMPS 12B Spring 2017
 * Date: 05/16/17
 *
 * Hashes a key string to an unsigned integer using AES encryption.
 *
 * @param salt An array of 4 32-bit unsigned ints to generate more 'random' hashes.
 * @param key  The string (const char to comply with strlen) to hash.
 * 
 * @return The hashed value.
 */
static inline uint32_t hash(uint32_t salt[], const char *key)
{
	uint32_t output[4] = { 0x0 };
	uint32_t sum = 0x0;
	
	int keyLen = strlen(key);
	int realLength = 16 * (keyLen / 16 + (keyLen % 16 ? 1 : 0));
	uint8_t *realKey = (uint8_t *) calloc(realLength, sizeof(uint8_t));

	memcpy(realKey, key, keyLen);
	
	for (int i = 0; i < realLength; i += 16)
	{
		AES128_ECB_encrypt((uint8_t *) salt,
				   (uint8_t *) realKey + i, // Input
				   (uint8_t *) output);     // Output
		sum ^= output[0] ^ output[1] ^ output[2] ^ output[3];
	}

	free(realKey);
	realKey = NIL;
	return sum;
}

# endif
