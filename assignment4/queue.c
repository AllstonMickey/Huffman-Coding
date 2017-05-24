# include <stdlib.h>
# include "queue.h"

/* typedef struct queue
 * {
 * 	uint32_t size;       // How big is it?
 * 	uint32_t head, tail; // Front and rear locations
 *	item *entries;       // Array of entries
 * } queue;
 */

queue *newQueue(uint32_t size)
{
	queue *q = (queue *) malloc(sizeof(queue));
	if (q)
	{
		q->entries = (item *) calloc(size, sizeof(item));
		if (q->entries)
		{
			q->size = size;
			q->head = q->tail = 0;
			return q;
		}
	}
	return (queue *) 0;
}

void delQueue(queue *q)
{
	free(q->entries);
	q->entries = NIL;
	free(q);
	q = NIL;
}

/*
 * Adds an entry to the front.
 *
 * @param q Queue to add to
 * @param i Entry to add
 * @return true  Success
 * 	   false Failure
 */
bool enqueue(queue *q, item i)
{

}

/*
 * Removes the rear entry (smallest value).
 *
 * @param q Queue to remove from
 * @param i Item to set to the removed entry
 * @return true  Success
 * 	   false Failure
 */
bool dequeue(queue *q, item *i)
{

}

bool empty(queue *q)
{

}

bool full(queue *q)
{

}

