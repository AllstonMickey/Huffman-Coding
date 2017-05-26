// TODO: stop accessing children out of the array bounds,
// 	 check if they are within the size first.

# ifndef _HEAP_H
# define _HEAP_H

# ifndef SWAP
# define SWAP(x, y) { queueItem t = x; x = y; y = t; ; }
# endif

# ifndef parent
# define parent(n) (n / 2)
# endif

# ifndef leftChild
# define leftChild(n) (2 * n)
# endif

# ifndef rightChild
# define rightChild(n) ((2 * n) + 1)
# endif

/* 
 * Sends the item at the end of the queue up the tree
 * until the heap properties are met.
 */
static inline void percolate(queue **q)
{
	uint32_t c = (*q)->head;
	while ((*q)->nodes[c] < (*q)->nodes[parent(c)])
	{
		SWAP((*q)->nodes[c], (*q)->nodes[parent(c)]);
		c = parent(c);
	}
}

/*
 * Checks which child has priority
 */
static inline int32_t comparison(queue *q, uint32_t p)
{
	return q->nodes[leftChild(p)] - q->nodes[rightChild(p)];
}

/*
 * Fixes the heap by checking which of its children has higher priority (if any).
 *
 * diff <  0: left child has priority (unless left child is 0 because it is not born)
 * diff >= 0: right child has priority (unless right child is 0)
 */
static inline void recede(queue **q)
{
	uint32_t c = ROOT;
	int32_t diff;
	while ((diff = comparison(*q, c)))
	{
		if (diff < 0) // right child has a larger value
		{
			if ((*q)->nodes[leftChild(c)])
			{
				SWAP((*q)->nodes[c], (*q)->nodes[leftChild(c)]);
				c = leftChild(c);
			}
			else
			{
				SWAP((*q)->nodes[c], (*q)->nodes[rightChild(c)]);
				c = rightChild(c);
			}
		}
		else
		{
			if ((*q)->nodes[rightChild(c)])
			{
				SWAP((*q)->nodes[c], (*q)->nodes[rightChild(c)]);
				c = rightChild(c);
			}
			else
			{
				SWAP((*q)->nodes[c], (*q)->nodes[leftChild(c)]);
				c = leftChild(c);
			}
		}
	}
}

# endif
