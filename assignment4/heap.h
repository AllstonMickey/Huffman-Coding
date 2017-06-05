# ifndef _HEAP_H
# define _HEAP_H

# ifndef SWAP
# define SWAP(x, y) { queueItem t = x; x = y; y = t; ; }
# endif

# ifndef parent
# define parent(n) ((n) / 2)
# endif

# ifndef leftChild
# define leftChild(n) (2 * (n))
# endif

# ifndef rightChild
# define rightChild(n) ((2 * (n)) + 1)
# endif

/* percolate:
 *
 * Sends the item at the end of the queue up the tree
 * until the heap properties are met.
 */
static inline void percolate(queue *q)
{
	uint32_t c = q->head;
	while (VALNODE(q, c) < VALNODE(q, parent(c)))
	{
		SWAP(q->nodes[c], q->nodes[parent(c)]);
		c = parent(c);
	}
}

/* favorite:
 *
 * Determines which child of the parent has the highest priority.
 */
uint32_t favorite(queue *q, uint32_t p)
{
	uint32_t l = leftChild(p);
	uint32_t r = rightChild(p);

	/*
	 * Makes sure the node exists before checking the value inside
	 *
	 * The right node cannot exist unless there is a left node so
	 * it is not necessary to check that case.
	 */

	if (l < q->head && r < q->head) // case 1: both nodes exist
	{
		if (VALNODE(q, l) <= VALNODE(q, r)) // case 1a: left < right
		{
			return l;
		}
		else // case 1b: right <= left
		{
			return r;
		}
	}
	else if (l < q->head) // case 2: one child (the left)
	{
		return l;
	}
	else // case 3: no children
	{
		return p;
	}
}

/* recede:
 *
 * Fixes the heap by checking which of the parent's children has higher priority (if any).
 *
 * Sends the root element down the tree until heap properties are met.
 *
 * Checks which child has priority over the other.
 * Checks if the that child has priority over the parent.
 * 	If it does, swap them.
 * 	If it does not, done.
 */
static inline void recede(queue *q)
{
	uint32_t p = ROOT;
	while (favorite(q, p) != p)
	{
		if (VALNODE(q, p) > VALNODE(q, favorite(q, p)))
		{
			uint32_t fav = favorite(q, p);
			SWAP(q->nodes[p], q->nodes[favorite(q, p)]);
			p = fav;
		}
		else
		{
			break;
		}
	}
}

# endif
