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

/*
 * Pushes an item onto a stack by using its composition of bits.
 *
 * Since each item is represented in binary at its most pure form,
 * we can push each bit of the item (in reverse order to make popping easier)
 * to represent the item itself.
 */
bool push(stack *s, item i)
{
	for (int32_t bit_i = ITEM_NBITS - 1; bit_i > -1; bit_i -= 1)
	{
		pushBit(s, VALBIT(i, bit_i));
	}
}

/*
 * Pushes a bit k onto a stack.
 */
bool pushBit(stack *s, bool k)
{
	if (fullStack(s) && s->fixed)
	{
		return false;
	}
	else if (fullStack(s))
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

/*
 * Uses bit shifting to pop bits and recreate the item.
 *
 * Using the facts that each stack we created has bits pushed onto it,
 * and a single partition/group width of bits is equal to the size
 * of the item in bits, we can pop c bits off the stack, where c is
 * the size of the item in bits.
 *
 * We can then store this result in a variable of value 0, popped, using
 * bit shifting.  Since popped is type item, the computer knows what this
 * bit representation is as that item, and therefore, does not confuse
 * chars vs uint8_t, uint32_t vs. treeNode, etc.
 */
bool pop(stack *s, item *i)
{
	if (emptyStack(s))
	{
		return false;
	}

	// for each bit in the item, pop the bit
	// store the result in an item using bit shifting
	item popped = 0x0;
	for (uint32_t j = 0; j < ITEM_NBITS; j += 1)
	{
		bool val;
		popBit(s, &val);
		if (val)
		{
			popped |= 0x1 << j;
		}
	}
	*i = popped;
	return true;
}

bool popBit(stack *s, bool *k)
{
	// for each bit in the item
	if (emptyStack(s))
	{
		return false;
	}

	s->top -= 1;
	*k = VALBIT(s->entries[s->top / ITEM_NBITS], s->top);
	return true;
}


// Checks if the stack is empty
bool emptyStack(const stack *s)
{
	return s->top == 0;
}

// Checks if the stack is full
bool fullStack(const stack *s)
{
	return s->top >= s->size;
}

void printStackItems(const stack *s)
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

void printStackBits(const stack *s)
{
	printf("top: %u\n", s->top);
	for (uint32_t i = 0; i < s->top; i += 1)
	{
		printf("%u", VALBIT(s->entries[i >> 3], i));
		if ((i + 1) % 4 == 0)
		{
			printf(" ");
		}
		if ((i + 1) % 8 == 0)
		{
			printf("\n");
		}
	}
	printf("\n");
}

