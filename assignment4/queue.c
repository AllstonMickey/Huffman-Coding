/*
 * Implementation of a priority queue as a binary min-heap
 */

# include <stdlib.h>
# include "queue.h"

# ifndef NIL
# define NIL (void *) 0
# endif

queue *newQueue(uint32_t size)
{
	queue *q = (queue *) malloc(sizeof(queue));
	if (q)
	{
		q->nodes = (queueItem *) calloc(size, sizeof(queueItem));
		if (q->nodes)
		{
			q->size = size;
			return q;
		}
	}
	return (queue *) 0;
}

void delQueue(queue *q)
{
	free(q->nodes);
	q->nodes = NIL;
	free(q);
	q = NIL;
}

/*
 * Adds an item to the queue
 */
bool enqueue(queue *q, queueItem i)
{
	
}

