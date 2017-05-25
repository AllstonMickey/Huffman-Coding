# ifndef _QUEUE_H
# define _QUEUE_H
# include <stdint.h>
# include <stdbool.h>

# ifndef NIL
# define NIL (void *) 0
# endif

typedef QUEUE_ITEM queueItem;

typedef struct queue
{
	uint32_t size;       // How big is it? (number of entries)
	uint32_t head, tail; // Front and rear locations
	queueItem *entries;       // Array to hold the entries
} queue;

queue *newQueue(uint32_t size);

void delQueue(queue *q);

// Adds an entry to the front
bool enqueue(queue *q, queueItem i);

// Removes the rear entry (smallest value) and sets i to it
bool dequeue(queue *q, queueItem *i);

// Is it empty?
bool empty(queue *q);

// Is it full?
bool full(queue *q);

# endif
