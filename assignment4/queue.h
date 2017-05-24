# ifndef _QUEUE_H
# define _QUEUE_H
# include <stdint.h>
# include <stdbool.h>

# ifndef NIL
# define NIL (void *) 0
# endif

typedef treeNode item; // treeNode defined in huffman.h

typedef struct queue
{
	uint32_t size;       // How big is it?
	uint32_t head, tail; // Front and rear locations
	item *entries;       // Array to hold the entries
} queue;

queue *newQueue(uint32_t size);

void delQueue(queue *q);

// Adds an entry to the front
bool enqueue(queue *q, item i);

// Removes the rear entry (smallest value) and sets i to it
bool dequeue(queue *q, item *i);

// Is it empty?
bool empty(queue *q);

// Is it full?
bool full(queue *q);

# endif
