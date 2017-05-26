# ifndef _HEAP_H
# define _HEAP_H

static inline uint32_t leftChild(uint32_t p)
{
	return 2 * p;
}

static inline uint32_t rightChild(uint32_t p)
{
	return (2 * p) + 1;
}

static inline uint32_t parent(uint32_t c)
{
	return c / 2;
}

static inline void fixHeap(queue **q)
{
	
}

# endif
