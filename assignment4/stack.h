# ifndef _STACK_H
# define _STACK_H
# include <stdint.h>
# include <stdbool.h>

# define item char

# ifndef NIL
# define NIL (void *) 0
# endif

typedef struct stack
{
	bool fixed;    // Dynamic or Fixed size?
	uint32_t top;  // Number of used bits
	uint32_t size; // Number of max bits (may realloc later if fixed is true)
	item *entries; // Array of whatever type is being held in the stack
} stack;

// Creates a stack occupying 'bytes' size
stack *newStack(uint32_t nbits, bool fixed);

void delStack(stack *s);

// Adds an entry to the top of the stack
bool push(stack *s, item i);
bool pushBit(stack *s, bool k);

// Removes an entry from the top of the stack
bool pop(stack *s, item *i);
bool popBit(stack *s, bool *k);

// Checks if the stack is empty
bool emptyStack(const stack *s);

// Checks if the stack is full
bool fullStack(const stack *s);

void printStackItems(const stack *s);

void printStackBits(const stack *s);

# endif
