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
# define MAX_BUF 128
# endif

ssize_t loadHist(char *file, uint32_t hist[]);
uint32_t enqueueHist(queue **q, uint32_t hist[]);
treeNode *buildTree(queue **q);
void writeOFile(char oFile[MAX_BUF], char sFile[MAX_BUF], uint64_t sFileLen,
		uint16_t leaves, treeNode *t, uint32_t hist[HIST_LEN], stack *codes[HIST_LEN]);

int main(int argc, char **argv)
{
	char in[MAX_BUF] = {'\0'};
	char out[MAX_BUF] = {'\0'};
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
	uint64_t sFileSize = (uint64_t) loadHist(in, histogram);
	printf("sFileSize: %u\n", sFileSize);

	/*
	 * Enqueue the histogram into a priority queue.
	 */

	queue *q = newQueue(HIST_LEN + 1); // +1 to account for the empty 0th index
	uint16_t leafCount = enqueueHist(&q, histogram);
	
	/*
	 * Constructs a Huffman Tree from the entries in the Queue.
	 */

	treeNode *huf = buildTree(&q);
	printTree(huf, 0);

	/*
	 * Build bit paths (as a stack) to the leaves from the root
	 */

	stack *path[HIST_LEN];
	stack *s = newStack(HIST_LEN, false);
	printf("Building leaf paths. . .\n");
	buildCode(huf, s, path);
	
	printf("\nPrinting resulting leaf paths. . .\n");
	for (uint16_t i = 0; i < HIST_LEN; i += 1)
	{
		if (histogram[i])
		{
			printf("path[%u]: ", i);
			printStackBits(path[i]);
		}
	}

	/*
	 * Write to Output File
	 */

	writeOFile(out, in, sFileSize, leafCount, huf, histogram, path);
	
	
	bitV *v = newVec(14);
	printf("before:\n"); printVec(v);
	//setBit(v, 3);
	appendStack(v, path[10]);
	appendStack(v, path[104]);
	appendStack(v, path[101]);
	printf("\nafter:\n"); printVec(v);
	printf("\n");
	
	delTree(huf);
	delQueue(q);
	return 0;
}

/* loadHist:
 *
 * Counts the number of occurrences of each byte in a file,
 * storing them in a histogram.
 */
ssize_t loadHist(char *file, uint32_t hist[])
{
	int fd = open(file, O_RDONLY);
	struct stat buffer;
	fstat(fd, &buffer);
	printf("bytes in file: %u\n", buffer.st_size);

	bitV *v = newVec(buffer.st_size * 8);
	ssize_t n = read(fd, v->v, buffer.st_size);
	printf("bytes read in: %d\n", n);

	for (ssize_t i = 0; i < buffer.st_size; i += 1)
	{
		hist[v->v[i]] += 1;
	}
	delVec(v);
	close(fd);
	return n;
}

/* enqueueHist:
 * 
 * Enqueues all 'active' entries of the histogram as treeNodes.
 * Priority is determined by the count of each node (the freq. in hist.)
 */
uint32_t enqueueHist(queue **q, uint32_t hist[])
{
	uint16_t leaves = 0;
	for (int i = 0; i < HIST_LEN; i += 1)
	{
		if (hist[i])
		{
			leaves += 1;
			treeNode *n = newNode(i, hist[i], true);
			enqueue(*q, *n);
			delNode(n);
		}
	}
	return leaves;
}

/* buildTree:
 *
 * Dequeues two nodes with the smallest counts and joins them under
 * a parent node.  Repeats until one node left in the queue (the root).
 * Returns the root node of the Huffman Tree as a pointer.
 */
treeNode *buildTree(queue **q)
{
	while ((*q)->head - 1 != ROOT)
	{
		treeNode l;
		treeNode r;
		dequeue(*q, &l);
		dequeue(*q, &r);

		treeNode *j = join(convert(l), convert(r));
		enqueue(*q, *j);
		delNode(j);
	}

	treeNode tree;
	dequeue(*q, &tree);
	return convert(tree);
}

void writeOFile(char oFile[MAX_BUF], char sFile[MAX_BUF], uint64_t sFileLen,
		uint16_t leaves, treeNode *t, uint32_t hist[HIST_LEN], stack *codes[HIST_LEN])
{
	int fdOut;
	if (oFile[0] == '\0')
	{
		fdOut = STDIN_FILENO;
	}
	else
	{
		fdOut = open(oFile, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU | S_IRGRP | S_IROTH);
	}

	if (fdOut == -1)
	{
		perror("Cannot open output file");
		return;
	}

	uint32_t magicNumber = 0xdeadd00d;
	uint16_t treeSize = (3 * leaves) - 1;
	
	write(fdOut, &magicNumber, sizeof(magicNumber));
	write(fdOut, &sFileLen, sizeof(sFileLen));
	write(fdOut, &treeSize, sizeof(treeSize));
	dumpTree(t, fdOut);
	
	/*
	 * Writes paths to the leaves for the bytes in the file
	 */

	int fdIn;
	if (sFile[0] == '\0')
	{
		fdIn = STDIN_FILENO;
	}
	else
	{
		fdIn = open(sFile, O_RDONLY);
	}

	if (fdIn == -1)
	{
		perror("Cannot open input file");
		return;
	}

	// read the bytes of sFile into bitV
	struct stat buffer;
	fstat(fdIn, &buffer);
	bitV *v = newVec(buffer.st_size * 8);
	ssize_t n = read(fdIn, v->v, buffer.st_size);

	for (int i = 0; i < n; i += 1)
	{
	}
}
