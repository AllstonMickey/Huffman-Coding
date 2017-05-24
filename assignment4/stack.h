# ifndef _STACK_H
# define _STACK_H
# include <stdint.h>
# include <stdbool.h>

# ifndef NIL
# define NIL (void *) 0
# endif

typedef void* item; // treeNode defined in huffman.h

typedef struct stack
{
	uint32_t size; // How big? (max # of entries)
	uint32_t top;  // Where is the top?
	item *entries; // Array to hold the stack's entries
} stack;

stack *newStack();

void delStack(stack *s);

item pop(stack *s);

void push(stack *s, item i);

// Is it empty?
bool empty(const stack *s);

// Is it full?
bool full(const stack *s);

void printStack(const stack *s);

# endif
