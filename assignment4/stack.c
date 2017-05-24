# include "stack.h"

stack *newStack(uint32_t nbits, bool fixed)
{
	stack *s = (stack *s) malloc(sizeof(stack));
	if (s)
	{
		s->entries = (item *) calloc((nbits / sizeof(item)) + 1, sizeof(item));
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

