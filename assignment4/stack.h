# ifndef _STACK_H
# define _STACK_H
# include <stdint.h>
# include <stdbool.h>
# include "huffman.h"

# ifndef NIL
# define NIL (void *) 0
# endif

typedef treeNode stackItem;

typedef struct stack
{
	uint32_t size; // How big? (max # of entries)
	uint32_t top;  // Where is the top?
	stackItem *entries; // Array to hold the stack's entries
} stack;

stack *newStack(uint32_t size);

void delStack(stack *s);

bool pop(stack *s, stackItem *i);

bool push(stack *s, stackItem i);

// Is it empty?
bool emptyStack(const stack *s);

// Is it full?
bool fullStack(const stack *s);

void printStack(const stack *s);

# endif
