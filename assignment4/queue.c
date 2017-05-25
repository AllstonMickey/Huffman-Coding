# include <stdlib.h>
# include "queue.h"

# ifndef NIL
# define NIL (void *) 0
# endif

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
		q->entries = (queueItem *) calloc(size, sizeof(queueItem));
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
bool enqueue(queue *q, queueItem i)
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
bool dequeue(queue *q, queueItem *i)
{

}

bool empty(queue *q)
{

}

bool full(queue *q)
{

}

