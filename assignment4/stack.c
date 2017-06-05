# include <stdlib.h>
# include <stdio.h>
# include "stack.h"

/*
 * Allocates a new stack of items
 */
stack *newStack(uint32_t size)
{
	stack *s = (stack *) malloc(sizeof(stack));
	if (s)
	{
		s->size = size;
		s->top = 0;
		s->entries = (stackItem *) calloc(s->size, sizeof(stackItem));
		if (s->entries)
		{
			return s;
		}
	}
	return (stack *) 0;
}

void delStack(stack *s)
{
	free(s->entries);
	s->entries = NIL;
	free(s);
	s = NIL;
}

/*
 * Removes the top entry
 *
 * @param s Stack to pop from
 * @return Popped entry
 */
bool pop(stack *s, stackItem *i)
{
	if (!emptyStack(s))
	{
		s->top -= 1;
		*i = s->entries[s->top];
		return true;
	}
	return false;
}

/*
 * Adds an entry to the top
 *
 * @param s Stack to add to
 * @param i Entry to add
 */
bool push(stack *s, stackItem i)
{
	if (fullStack(s))
	{
		stackItem *tmp = (stackItem *) realloc(s->entries, sizeof(stackItem) * s->size * 2);
		if (tmp)
		{
			s->size *= 2; // double size to reduce number of realloc calls
			s->entries = tmp;
		}
		else
		{
			free(tmp);
			tmp = NIL;
			return false;
		}
	}
	s->entries[s->top] = i;
	s->top += 1;
	return true;
}

bool emptyStack(const stack *s)
{
	return s->top == 0;
}

bool fullStack(const stack *s)
{
	return s->top == s->size;
}

/*
 * Debugging function to print each entry (address) in the stack,
 * the top of the stack, and the size.
 */
void printStack(const stack *s)
{
	printf("top: %u\n", s->top);
	printf("size: %u\n", s->size);
	for (uint32_t i = 0; i < s->size; i += 1)
	{
		printf("s->entries[%u]: %c (%u) %lu %u\n", i, (char) s->entries[i].symbol, s->entries[i].symbol,
				s->entries[i].count, s->entries[i].leaf);
	}
}

