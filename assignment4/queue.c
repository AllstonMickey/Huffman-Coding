/*
 * Implementation of a priority queue as a binary min-heap
 */

# include <stdlib.h>
# include "queue.h"
# include "heap.h"

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
			q->len = 1; // furthest element away from 0th index
			q->nodes[0] = (queueItem) 0; // 0 element is empty to maintain arithmetic properties
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

bool fullQueue(queue *q)
{
	return q->len == q->size;
}

bool emptyQueue(queue *q)
{
	return q->len == 1;
}

