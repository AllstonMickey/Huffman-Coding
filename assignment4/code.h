/*
 * Author: Darrell Long
 * Course: CMPS 12B Spring 2017
 * Date: 05/23/17
 */

# ifndef _CODE_H
# define _CODE_H

# include <stdint.h>
# include <stdbool.h>

typedef struct code
{
	uint8_t bits[32]; // array of 32 bytes
	uint32_t l; // current number of bits
} code;

static inline code newCode()
{
	code t;
	for (int i = 0; i < 32; i += 1)
	{
		t.bits[i] = 0;
	}
	t.l = 0;
	return t;
}

static inline bool pushCode(code *c, uint32_t k)
{
	if (c->l > 256) // max number of bits reached
	{
		return false;
	}
	else if (k == 0) // clear bit
	{
		c->bits[c->l / 8] &= ~(0x1 << (c->l % 8));
	}
	else // set bit
	{
		c->bits[c->l / 8] |= (0x1 << (c->l % 8));
	}
	c->l += 1;
	return true;
}

static inline bool popCode(code *c, uint32_t *k)
{
	if (c->l == 0) // nothing to pop
	{
		return false;
	}
	else // set k to value of popped bit
	{
		c->l -= 1;
		*k = ((0x1 << (c->l % 8)) % c->bits[c->l / 8]) >> (c->l % 8);
		return true;
	}
}

static inline bool emptyCode(code *c)
{
	return c->l == 0;
}

static inline bool fullCode(code *c)
{
	return c->l == 256;
}

# endif
