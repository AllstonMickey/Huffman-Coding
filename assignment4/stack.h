# ifndef _STACK_H
# define _STACK_H
# include <stdint.h>
# include <stdbool.h>

# ifndef NIL
# define NIL (void *) 0
# endif

typedef STACK_ITEM stackItem;

typedef struct stack
{
	bool fixed;    // Dynamic or Fixed size?
	uint32_t top;  // Number of used bits
	uint32_t size; // Number of max bits (may realloc later if fixed is true)
	stackItem *entries; // Array of whatever type is being held in the stack
} stack;

stack *newStack(uint32_t nbits, bool fixed);

stack *deepCopyStack(stack *s, bool fixed, bool extras);

void delStack(stack *s);

// Adds an entry to the top of the stack
bool push(stack *s, stackItem i);
bool pushBit(stack *s, bool k);

// Removes an entry from the top of the stack
bool pop(stack *s, stackItem *i);
bool popBit(stack *s, bool *k);

// Checks if the stack is empty
bool emptyStack(const stack *s);

// Checks if the stack is full
bool fullStack(const stack *s);

void printStackItems(const stack *s);

void printStackBits(const stack *s);

# endif
