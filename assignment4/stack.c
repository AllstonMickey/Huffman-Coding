# include <stdlib.h>
# include "stack.h"

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
		s->size = 256;
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

