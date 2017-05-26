/*
 * Implementation of a priority queue as a binary min-heap
 */

# include <stdio.h>
# include <stdlib.h>
# include "queue.h"
# include "heap.h"

queue *newQueue(uint32_t size)
{
	queue *q = (queue *) malloc(sizeof(queue));
	if (q)
	{
		q->nodes = (queueItem *) calloc(size, sizeof(queueItem));
		if (q->nodes)
		{
			q->size = size;
			q->nodes[0] = (queueItem) 0x0; // 0th index is empty to maintain heap properties
			q->head = ROOT;
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
	if (fullQueue(q))
	{
		return false;
	}
	
	q->nodes[q->head] = i;
	if (!emptyQueue(q))
	{
		percolate(&q);
	}
	q->head += 1;
	
	return true;
}

bool fullQueue(queue *q)
{
	return q->head == q->size;
}

bool emptyQueue(queue *q)
{
	return q->head == ROOT;
}

void printQueue(queue *q)
{
	for (uint32_t i = 0; i < q->size; i += 1)
	{
		printf("%u, %u\n", i, q->nodes[i]);
	}
}

