# include "stack.h"
# include <stdlib.h>
# include <stdio.h>

# ifndef VALBIT
# define VALBIT(v, k) (v[k >> 3] & (0x1 << (k % 8))) >> (k % 8)
# endif

# ifndef BITS
# define BITS 8
# endif

# ifndef ITEM_NBITS
# define ITEM_NBITS (sizeof(item) * BITS)
# endif

stack *newStack(uint32_t nbits, bool fixed)
{
	stack *s = (stack *) malloc(sizeof(stack));
	if (s)
	{
		s->entries = (item *) calloc(nbits / ITEM_NBITS, sizeof(item));
		if (s->entries)
		{
			s->fixed = fixed;
			s->size = nbits;
			s->top = 0;
			return s;
		}
	}
	return (stack *) 0;
}

/*
   void delStack(stack *s);
 */

void valBits(item element)
{
	for (uint32_t i = 0; i < ITEM_NBITS; i += 1)
	{
		bool val = (element & (0x1 << (i % ITEM_NBITS))) >> (i % ITEM_NBITS);
		printf("val, %u: %u\n", i, val);
	}
}

// Adds an entry to the top of the stack
bool push(stack *s, uint16_t element)
{
	printf("%u\n", element);
	for (uint32_t i = 0; i < sizeof(uint16_t) * 8; i += 1)
	{
		bool val = (element & (0x1 << (element % 16))) >> (element % 16);
		printf("val, %u: %u\n", i, val);
	}
}

bool pushBit(stack *s, bool k)
{
	if (s->top > 256) { return false; }
	else if (!k)
	{
		s->entries[s->top / 8] &= ~(0x1 << (s->top % 8));
	}
	else
	{
		s->entries[s->top / 8] |= (0x1 << (s->top % 8));
	}
	s->top += 1;
	return true;
}

/*
// Removes an entry from the top of the stack
bool pop(stack *s, item *i);

// Checks if the stack is empty
bool empty(const stack *s);
*/

// Checks if the stack is full
bool full(const stack *s)
{
	return s->top == s->size;
}

void printItems(const stack *s)
{
	printf("top:  %u\n", s->top);
	printf("size: %u\n", s->size);
	uint32_t i = 0;
	while (i < s->size)
	{
		printf("%p\n", s->entries[i]);
		i += ITEM_NBITS;
	}
}

void printBits(const stack *s)
{
	printf("top: %u\n", s->top);
	for (uint32_t i = 0; i < s->size; i += 1)
	{
		printf("%u", VALBIT(s->entries, i));
		if ((i + 1) % 4 == 0) { printf(" ");  }
		if ((i + 1) % 8 == 0) { printf("\n"); }
	}
}
