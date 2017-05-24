# include <stdlib.h>
# include "stack.h"

# ifndef MIN_STACK
# define MIN_STACK 16
# endif

/* typedef struct stack
{
	uint32_t size; // How big?
	uint32_t top;  // Where is the top?
	void *entries; // Array of any object
} stack; */

stack *newStack()
{
	stack *s = (stack *) malloc(sizeof(stack));
	if (s)
	{
		s->size = MIN_STACK;
		s->top = 0;
		s->entries = (void *) calloc(s->size, sizeof(void));
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

// Removes the top element and stores it in e
void pop(stack *s, void *e)
{
	
}

bool empty(stack *s)
{
	return s->top == 0;
}
