# ifndef _STACK_H
# define _STACK_H
# include <stdint.h>
# include <stdbool.h>

# ifndef NIL
# define NIL (void *) 0
# endif

typedef struct stack
{
	uint32_t size; // How big?
	uint32_t top;  // Where is the top?
	void **entries; // Array of pointers to any objects
} stack;

stack *newStack();

void delStack(stack *s);

// Removes the top element and stores it in e
void pop(stack *s, void **e);

// Adds an element to the top of the stack
void push(stack *s, void *e);

// Is it empty?
bool empty(stack *s);

// Is it full?
bool full(stack *s);

void printStack(stack *s);

# endif
