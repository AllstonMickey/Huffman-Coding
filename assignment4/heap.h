# ifndef _HEAP_H
# define _HEAP_H

# ifndef SWAP
# define SWAP(x, y) { queueItem t = x; x = y; y = t; ; }
# endif

# ifndef leftChild
# define leftChild(p) (2 * p)
# endif

# ifndef rightChild
# define rightChild(p) ((2 * p) + 1)
# endif

# ifndef parent
# define parent(c) (c / 2)
# endif


static inline void percolate(queue **q)
{
	uint32_t i = (*q)->head;
	{
		while ((*q)->nodes[i] < (*q)->nodes[parent(i)])
		{
			SWAP((*q)->nodes[i], (*q)->nodes[parent(i)]);
			i = parent(i);
		}
	}
}

# endif
