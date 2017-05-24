# include <stdlib.h>
# include "queue.h"

/* typedef struct queue
 * {
 * 	uint32_t size;       // How big is it?
 * 	uint32_t head, tail; // Front and rear locations
 *	item *Q;             // Array of entries
 * } queue;
 */

queue *newQueue(uint32_t size)
{
	
}

void delQueue(queue *q)
{

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

