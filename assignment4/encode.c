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

void populateHistogram(char *file, uint32_t hist[]);
void enqueueHist(queue **q, uint32_t hist[]);

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
	
	/* QUEUE TESTING with treeNode as the item
	treeNode *nodes = calloc(3, sizeof(treeNode));
	
	treeNode *t = newNode(0, 15, false);
	treeNode *l = newNode(0, 7, false);
	treeNode *r = newNode(0, 2, false);
	
	queue *q = newQueue(5);
	enqueue(q, *t); enqueue(q, *l); enqueue(q, *r);
	printQueue(q);

	treeNode res[3];
	dequeue(q, &res[0]);
	printQueue(q);
	dequeue(q, &res[1]);
	printQueue(q);
	dequeue(q, &res[2]);
	printQueue(q);
	*/

	while (in[0] == '\0')
	{
		printf("Enter an input file path: ");
		scanf("%s", in);
	}

	uint32_t histogram[HIST_LEN] = {0};
	histogram[0] = 1;
	histogram[HIST_LEN - 1] = 1;
	populateHistogram(in, histogram);
	
	for (uint16_t i = 0; i < HIST_LEN; i += 1)
	{
		printf("%u: %u\n", i, histogram[i]);
	}

	queue *histQueue = newQueue(HIST_LEN);
	enqueueHist(&histQueue, histogram);
	printQueue(histQueue);	

	return 0;
}

/*
 * Counts the number of occurrences of each byte in a file,
 * storing them in a histogram.
 *
 * @param file Path to the file to read from
 * @param hist Array to store the occurrences
 */
void populateHistogram(char *file, uint32_t hist[])
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
}

void enqueueHist(queue **q, uint32_t hist[])
{
	for (int i = 0; i < HIST_LEN; i += 1)
	{
		if (hist[i])
		{
			treeNode *n = newNode(i, hist[i], true);
			enqueue(*q, *n);
		}
	}
}

