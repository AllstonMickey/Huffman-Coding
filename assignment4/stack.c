# include <stdlib.h>
# include <stdio.h>
# include "stack.h"

# ifndef MIN_STACK
# define MIN_STACK 16
# endif

/*
 * Allocates a new stack of void pointers
 */
stack *newStack()
{
	stack *s = (stack *) malloc(sizeof(stack));
	if (s)
	{
		s->size = MIN_STACK;
		s->top = 0;
		s->entries = (void **) calloc(s->size, sizeof(void *));
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
 * Removes the top entry and stores it
 *
 * @param s Stack to pop from
 * @param e The void pointer to store the popped entry
 */
void pop(stack *s, void **e)
{
	if (!empty(s))
	{
		s->top -= 1;
		*e = s->entries[s->top];
		s->entries[s->top] = NIL;
	}
}

/*
 * Adds an entry to the top
 *
 * @param s Stack to add to
 * @param e The address to add
 */
void push(stack *s, void *e)
{
	if (full(s))
	{
		void **tmp = s->entries;
		tmp = (void **) realloc(s->entries, sizeof(void *) * s->size * 2);
		if (tmp)
		{
			s->size *= 2;
			for (uint32_t i = s->top; i < s->size; i += 1)
			{
				tmp[i] = NIL;
			}
			s->entries = tmp;
		}
	}
	s->entries[s->top] = e;
	s->top += 1;
}

bool empty(stack *s)
{
	return s->top == 0;
}

bool full(stack *s)
{
	return s->top == s->size;
}

/*
 * Debugging function to print each entry (address) in the stack,
 * the top of the stack, and the size.
 */
void printStack(stack *s)
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

