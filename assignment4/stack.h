# ifndef _GENERIC_STACK_H
# define _GENERIC_STACK_H
# include <stdint.h>
# include <stdbool.h>

# ifndef NIL
# define NIL (void *) 0
# endif

typedef uint8_t item; // define an item as 1 byte

typedef stack
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

// Removes an entry from the top of the stack
bool pop(stack *s, item *i);

// Checks if the stack is empty
bool empty(const stack *s);

// Checks if the stack is full
bool full(const stack *s);

# endif
