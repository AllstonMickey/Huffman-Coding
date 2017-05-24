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
		s->entries = (item *) calloc(s->size, sizeof(item));
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
item pop(stack *s)
{
	if (!empty(s))
	{
		s->top -= 1;
		item i = s->entries[s->top];
		s->entries[s->top] = NIL;
		return i;
	}
}

/*
 * Adds an entry to the top
 *
 * @param s Stack to add to
 * @param i Entry to add
 */
void push(stack *s, item i)
{
	if (full(s))
	{
		item *tmp = s->entries;
		tmp = (item *) realloc(s->entries, sizeof(item) * s->size * 2);
		if (tmp)
		{
			s->size *= 2; // double size to reduce number of realloc calls
			
			// set all unused realloc entries to NIL
			for (uint32_t i = s->top; i < s->size; i += 1)
			{
				tmp[i] = NIL;
			}
				
			s->entries = tmp;
		}
	}
	s->entries[s->top] = i;
	s->top += 1;
}

bool empty(const stack *s)
{
	return s->top == 0;
}

bool full(const stack *s)
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
	uint32_t i = 0;
	while (i < s->size)
	{
		printf("%p\n", s->entries[i]);
		i += 1;
	}
}

