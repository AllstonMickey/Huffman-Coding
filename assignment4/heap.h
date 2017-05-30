// TODO: stop accessing children out of the array bounds,
// 	 check if they are within the size first.

# ifndef _HEAP_H
# define _HEAP_H

// treeNode t;
// t->count; // returns count of the node
// queueItem *nodes; // array of treeNodes

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
	while (VALNODE(*q, c) < VALNODE(*q, parent(c)))
	{
		SWAP((*q)->nodes[c], (*q)->nodes[parent(c)]);
		c = parent(c);
	}
}

uint32_t favorite(queue *q, uint32_t p)
{
	uint32_t l = leftChild(p);
	uint32_t r = rightChild(p);

	/*
	 * Makes sure the node exists before checking the value inside
	 * Returns the node with highest priority
	 */
	if (l < q->head && r < q->head) // both nodes exist
	{
		if (VALNODE(q, l) < VALNODE(q, r)) // left gets priority
		{
			return l;
		}
		else if (VALNODE(q, l) > VALNODE(q, r)) // right gets priority
		{
			return r;
		}
		else // no priority, return parent's index
		{
			return p;
		}
	}
	else if (l < q->head) // only left child exists, return left
	{
		return l;
	}
	else // no child exists, return parent
	{
		return p;
	}
}

/*
 * Fixes the heap by checking which of the parent's children has higher priority (if any).
 *
 * Sends the root element down the tree until heap properties are met.
 */
static inline void recede(queue **q)
{
	uint32_t p = ROOT;
	while (favorite(*q, p) != p)
	{
		if (VALNODE(*q, p) > VALNODE(*q, favorite(*q, p)))
		{
			SWAP((*q)->nodes[p], (*q)->nodes[favorite(*q, p)]);
			p = favorite(*q, p);
		}
		else
		{
			break;
		}
	}
}

# endif
