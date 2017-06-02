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
			VALNODE(q, 0) = 0; // 0th index is empty to maintain heap properties
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
 * Adds an item to the queue and puts it in its
 * correct position in the queue, dependent on its priority.
 *
 * Smaller VALNODEs percolate up to the top of the tree.
 *
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
		percolate(q);
	}
	q->head += 1;
	
	return true;
}

/*
 * Since the queue is a binary heap, the smallest element
 * (and thus, greatest priority), is at the root.
 *
 * Dequeue the root and fix the heap with recede()
 * in order to maintain the binary heap properties.
 */
bool dequeue(queue *q, queueItem *i)
{
	if (emptyQueue(q))
	{
		return false;
	}

	*i = q->nodes[ROOT];
	q->head -= 1;
	q->nodes[ROOT] = q->nodes[q->head];
	VALNODE(q, q->head) = 0;
	recede(q);
	return true;
}

// Is it full?
bool fullQueue(queue *q)
{
	return q->head == q->size;
}

// Is it empty?
bool emptyQueue(queue *q)
{
	return q->head == ROOT;
}

void printQueue(queue *q)
{
	printf("Printing queue...\n");
	for (uint32_t i = 0; i < q->size; i += 1)
	{
		printf("pos %u: %u\n", i, VALNODE(q, i));
	}
}
