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
		uint32_t nmemb = (nbits / ITEM_NBITS) + 1;
		s->entries = (item *) calloc(nmemb, sizeof(item));
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

// Adds an entry to the top of the stack
bool push(stack *s, item i)
{
	if (s->fixed && full(s))
	{
		return false;
	}
	else if (full(s))
	{
		item *tmp = s->entries;
		uint32_t nmemb = ((s->size / ITEM_NBITS) * 2) + 1;
		tmp = (item *) realloc(s->entries, nmemb * sizeof(item));
		if (tmp)
		{
			s->size *= 2;
			s->entries = tmp;
		}
	}

	if (i)
	{
		s->entries[s->top / ITEM_NBITS] |= (0x1 << (s->top % ITEM_NBITS));
	}
	else
	{
		s->entries[s->top / ITEM_NBITS] &= ~(0x1 << (s->top % ITEM_NBITS));
	}
	s->top += ITEM_NBITS;
	return s;
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
