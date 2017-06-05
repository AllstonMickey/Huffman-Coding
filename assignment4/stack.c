# include <stdlib.h>
# include <stdio.h>
# include "stack.h"

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

/* pop:
 *
 * Removes the top item.
 *
 * Sets stackItem *i to the popped item.
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

/* push:
 *
 * Adds an item to the top.
 * Reallocs an additional 'size' of the stack if it is full.
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

