# include "stack.h"
# include <stdlib.h>
# include <stdio.h>

# ifndef VALBIT
# define VALBIT(a, k) (a & (0x1 << (k % ITEM_NBITS))) >> (k % ITEM_NBITS)
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
		s->entries = (item *) calloc((nbits / ITEM_NBITS) + 1, sizeof(item));
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
	for (int32_t bit_i = ITEM_NBITS - 1; bit_i > -1; bit_i -= 1)
	{
		pushBit(s, VALBIT(i, bit_i));
	}
}

/*
 * TODO: check if stack is fixed
 * 	 realloc if not fixed and full
 * 	 push if space is available
 */
bool pushBit(stack *s, bool k)
{
	if (full(s) && s->fixed)
	{
		return false;
	}
	else if (full(s))
	{
		item *tmp = s->entries;
		tmp = (item *) realloc(s->entries, ((2 * s->size / ITEM_NBITS) + 1) * sizeof(item));
		if (tmp)
		{
			s->entries = tmp;
			s->size *= 2;
		}
		else
		{
			tmp = NIL;
		}
	}
	
	if (k)
	{
		s->entries[s->top / ITEM_NBITS] |= (0x1 << (s->top % ITEM_NBITS));
	}
	else
	{
		s->entries[s->top / ITEM_NBITS] &= ~(0x1 << (s->top % ITEM_NBITS));
	}
	s->top += 1;
	return true;
}

// TODO
// Removes an entry from the top of the stack
// sets e to the popped item
bool pop(stack *s, item *i)
{
	/*
	 * For each bit in item e, pop it off the stack
	 * (remember, this will pop the bits off in reverse order of binary representation)
	 *
	 * Concatenate the bits together and set it equal to the item.
	 */
	item popped = 0x0;
	for (uint32_t j = 0; j < ITEM_NBITS; j += 1)
	{
		bool val;
		popBit(s, &val);
		printf("val, %u: %u\n", j, val);
		if (val)
		{
			popped |= 0x1 << j;
		}
	}
	*i = popped;
}

// TODO
bool popBit(stack *s, bool *k)
{
	// for each bit in the item
	if (empty(s))
	{
		return false;
	}

	s->top -= 1;
	*k = VALBIT(s->entries[s->top / ITEM_NBITS], s->top);
	return true;
}


// Checks if the stack is empty
bool empty(const stack *s)
{
	return s->top == 0;
}

// Checks if the stack is full
bool full(const stack *s)
{
	return s->top >= s->size;
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
		printf("%u", VALBIT(s->entries[i >> 3], i));
		if ((i + 1) % 4 == 0) { printf(" ");  }
		if ((i + 1) % 8 == 0) { printf("\n"); }
	}
	printf("\n");
}
