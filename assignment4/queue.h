# ifndef _QUEUE_H
# define _QUEUE_H
# include <stdint.h>
# include <stdbool.h>

# ifndef NIL
# define NIL (void *) 0
# endif

# ifndef ROOT
# define ROOT 1
# endif

# ifndef VALNODE
# define VALNODE(q, n) ((q)->nodes[n].count)
# endif

typedef QUEUE_ITEM queueItem;

typedef struct queue
{
	uint32_t size;    // How big is it? (number of entries)
	uint32_t head;    // Where is the next element?
	queueItem *nodes; // Array of nodes for the heap
} queue;

queue *newQueue(uint32_t size);

void delQueue(queue *q);

// Adds an item to the queue
bool enqueue(queue *q, queueItem i);

// Removes the smallest item from the queue
bool dequeue(queue *q, queueItem *i);

// Is it full?
bool fullQueue(queue *q);

// Is it empty?
bool emptyQueue(queue *q);

void printQueue(queue *q);

# endif
