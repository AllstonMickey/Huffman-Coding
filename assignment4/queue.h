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
	uint32_t size;    // How big is it? (number of entries)
	uint32_t len;     // How many entries are there?
	queueItem *nodes; // Array of nodes for the heap
} queue;

queue *newQueue(uint32_t size);

void delQueue(queue *q);

bool enqueue(queue *q, queueItem i);

bool fullQueue(queue *q);

bool emptyQueue(queue *q);

# endif
