# include <sys/types.h> // fstat
# include <sys/stat.h>  // fstat
# include <fcntl.h>     // fstat
# include <unistd.h>    // read
# include <getopt.h>
# include <string.h>
# include "bv.h"        // bit vectors, stdint, stdio, stdlib
# include "huffman.h"   // huffman trees, stacks, stdint, stdbool
# include "queue.h"     // queues, heaps, stdint, stdbool

# ifndef HIST_LEN
# define HIST_LEN 256
# endif

# ifndef MAX_BUF
# define MAX_BUF 127
# endif

# ifndef ISLEAF
# define ISLEAF true
# endif

void loadHist(char *file, uint32_t hist[]);
void enqueueHist(queue **q, uint32_t hist[]);
void buildTree(queue **q);

int main(int argc, char **argv)
{
	char in[MAX_BUF] = {0};
	char out[MAX_BUF] = {0};
	bool verbose = false;

	int opt;
	while ((opt = getopt(argc, argv, "i:o:v")) != -1)
	{
		switch (opt)
		{
			case 'i':
				{
					strncpy(in, optarg, sizeof(char) * MAX_BUF);
					// strncpy does not null-term strings if the buf is maxed in size
					if (in[MAX_BUF - 1] != '\0')
					{
						in[MAX_BUF - 1] = '\0';
					}	
					break;
				}
			case 'o':
				{
					strncpy(out, optarg, sizeof(char) * MAX_BUF);
					// strncpy does not null-term strings if the buf is maxed in size
					if (out[MAX_BUF - 1] != '\0')
					{
						out[MAX_BUF - 1] = '\0';
					}
					break;
				}
			case 'v':
				{
					verbose = true;
					break;
				}
			case '?':
				{
					break;
				}
			default:
				{
					break;
				}
		}
	}

	while (in[0] == '\0')
	{
		printf("Enter an input file path: ");
		scanf("%s", in);
	}

	/*
	 * Make a histogram of byte frequency from the input file.
	 */

	uint32_t histogram[HIST_LEN] = {0};
	histogram[0] = 1;
	histogram[HIST_LEN - 1] = 1;
	loadHist(in, histogram);

	/*
	 * Enqueue the histogram into a priority queue.
	 */

	queue *q = newQueue(HIST_LEN);
	enqueueHist(&q, histogram);
	printQueue(q);	
	
	/*
	 * Create a treeNode as the root of the Huffman Tree.
	 * Build the tree by repeatedly dequeuing and joining nodes from the queue.
	 */

	buildTree(&q);
	treeNode huf;
	dequeue(q, &huf);
	printf("%u\n", huf.count);

	delQueue(q);
	return 0;
}

/* loadHist:
 *
 * Counts the number of occurrences of each byte in a file,
 * storing them in a histogram.
 */
void loadHist(char *file, uint32_t hist[])
{
	int fd = open(file, O_RDONLY);
	struct stat buffer;
	fstat(fd, &buffer);
	printf("bytes in file: %u\n", buffer.st_size);

	bitV *v = newVec(buffer.st_size * 8);
	int64_t n = read(fd, v->v, buffer.st_size);
	printf("bytes read in: %d\n", n);

	for (uint64_t i = 0; i < buffer.st_size; i += 1)
	{
		hist[v->v[i]] += 1;
	}
	delVec(v);
}

/* enqueueHist:
 * 
 * Enqueues all 'active' entries of the histogram as treeNodes.
 * Priority is determined by the count of each node (the freq. in hist.)
 */
void enqueueHist(queue **q, uint32_t hist[])
{
	for (int i = 0; i < HIST_LEN; i += 1)
	{
		if (hist[i])
		{
			treeNode *n = newNode(i, hist[i], ISLEAF);
			enqueue(*q, *n);
			delNode(n);
		}
	}
}

/* buildTree:
 *
 * Dequeues two nodes with the smallest counts and joins them under
 * a parent node.  Repeat until one node left in the queue (the root).
 */
void buildTree(queue **q)
{
	while ((*q)->head - 1 != ROOT)
	{
		treeNode l, r, *j;
		dequeue(*q, &l);
		dequeue(*q, &r);
		j = join(&l, &r);
		enqueue(*q, *j);
		delNode(j);
	}
}
