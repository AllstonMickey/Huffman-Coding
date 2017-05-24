# include "stack.h"
# include <stdlib.h>
# include <stdio.h>

# ifndef VALBIT_VEC
# define VALBIT_VEC(v, k) (v[k >> 3] & (0x1 << (k % 8))) >> (k % 8)
# endif

# ifndef VALBIT_ITEM
# define VALBIT_ITEM(i, k) (i & (0x1 << (k % ITEM_NBITS))) >> (k % ITEM_NBITS)
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

// Adds an entry to the top of the stack
bool push(stack *s, item i)
{
	for (uint32_t j = 0; j < ITEM_NBITS; j += 1)
	{
		printf("val, %u: %u\n", j, VALBIT_ITEM(i, j));
		pushBit(s, VALBIT_ITEM(i, j));
	}
}

/*
 * TODO: check if stack is fixed
 * 	 realloc if not fixed and full
 * 	 push if space is available
 */
bool pushBit(stack *s, bool k)
{
	if (s->top > 256) { return false; }
	else if (!k)
	{
		s->entries[s->top / ITEM_NBITS] &= ~(0x1 << (s->top % ITEM_NBITS));
	}
	else
	{
		s->entries[s->top / ITEM_NBITS] |= (0x1 << (s->top % ITEM_NBITS));
	}
	s->top += 1;
	return true;
}

// TODO
// Removes an entry from the top of the stack
bool pop(stack *s, item *e)
{
	/*
	 * For each bit in item e, pop it off the stack
	 * (remember, this will pop the bits off in reverse order of binary representation)
	 *
	 * Concatenate the bits together and set it equal to the item.
	 */
	for (uint32_t j = 0; j < ITEM_NBITS; j += 1)
	{
		
	}
}

// TODO
bool popBit(stack *s, bool k)
{
}


// Checks if the stack is empty
bool empty(const stack *s)
{
	return s->top == 0;
}

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
		printf("%u", VALBIT_VEC(s->entries, i));
		if ((i + 1) % 4 == 0) { printf(" ");  }
		if ((i + 1) % 8 == 0) { printf("\n"); }
	}
	printf("\n");
}
