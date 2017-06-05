/* Implementation of a priority queue as a binary min-heap
 * 
 * Since the Huffman Tree being constructed can only have a maximum
 * of 256 nodes enqueued, the advantages of the min-heap priority queue are
 * not emphasized, but a binary min-heap seemed like a challenging yet rewarding
 * learning experience.  An implementation of a priority queue as a circular array
 * would have similar time complexities in this instance, but not as beneficial to my education.
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

/* enqueue:
 *
 * Adds an item to the queue and puts it in its
 * correct position in the queue, dependent on its priority.
 *
 * Smaller VALNODEs percolate up to the top of the tree.
 *
 * Returns whether the item was successfully enqueued or not.
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

/* dequeue:
 *
 * Since the queue is a binary min-heap, the smallest element
 * (and thus, greatest priority), is at the root.
 *
 * Dequeue the root and fix the heap with recede()
 * in order to maintain the binary heap properties.
 *
 * Returns whether the item was succesfully dequeued or not.
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

