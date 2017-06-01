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
uint64_t writeOFile(char oFile[MAX_BUF], char sFile[MAX_BUF], uint64_t sFileBytes,
		uint16_t leaves, treeNode *t, uint32_t hist[HIST_LEN], stack *codes[HIST_LEN]);
uint64_t dumpCodes(int outputFildes, char sFile[MAX_BUF], stack *codes[HIST_LEN]);
void printStatistics(uint64_t sFileBits, uint64_t oFileBits, uint16_t leaves);

int main(int argc, char **argv)
{
	char in[MAX_BUF] = {'\0'};
	char out[MAX_BUF] = {'\0'};
	bool verbose = false; // print statistics?
	bool pFlag = false;   // print the Huffman tree?
	bool sFlag = false;   // print the stacks for each leaf?

	int opt;
	while ((opt = getopt(argc, argv, "i:o:vps")) != -1)
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
			case 'p':
				{
					pFlag = true;
					break;
				}
			case 's':
				{
					sFlag = true;
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

	uint32_t histogram[HIST_LEN] = {0};
	histogram[0] = 1;
	histogram[HIST_LEN - 1] = 1;
	uint64_t inputNBytes = (uint64_t) loadHist(in, histogram);

	queue *q = newQueue(HIST_LEN + 1); // +1 to account for the empty 0th index
	uint16_t leafCount = enqueueHist(&q, histogram);

	treeNode *huf = buildTree(&q);

	stack *path[HIST_LEN];
	stack *s = newStack(HIST_LEN, false);
	buildCode(huf, s, path);

	uint64_t outputNBits = writeOFile(out, in, inputNBytes, leafCount, huf, histogram, path);

	if (verbose)
	{
		printStatistics(inputNBytes * 8, outputNBits, leafCount);
	}
	if (pFlag)
	{
		printTree(huf, 0);
	}
	if (sFlag)
	{
		for (uint16_t i = 0; i < HIST_LEN; i += 1)
		{
			if (histogram[i])
			{
				printf("path[%u]: ", i);
				printStackBits(path[i]);
			}
		}
	}

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

	bitV *v = newVec(buffer.st_size * 8);
	ssize_t n = read(fd, v->v, buffer.st_size);

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

uint64_t writeOFile(char oFile[MAX_BUF], char sFile[MAX_BUF], uint64_t sFileBytes,
		uint16_t leaves, treeNode *t, uint32_t hist[HIST_LEN], stack *codes[HIST_LEN])
{
	int fdOut;
	if (oFile[0])
	{
		fdOut = open(oFile, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU | S_IRGRP | S_IROTH);
	}
	else
	{
		fdOut = STDIN_FILENO;
	}

	if (fdOut == -1)
	{
		perror("Cannot open output file");
		return 0;
	}

	uint32_t magicNumber = 0xdeadd00d;
	uint16_t treeSize = (3 * leaves) - 1;

	write(fdOut, &magicNumber, sizeof(magicNumber));
	write(fdOut, &sFileBytes, sizeof(sFileBytes));
	write(fdOut, &treeSize, sizeof(treeSize));
	dumpTree(t, fdOut);
	return dumpCodes(fdOut, sFile, codes);
}

uint64_t dumpCodes(int outputFildes, char sFile[MAX_BUF], stack *codes[HIST_LEN])
{
	int fdIn;
	if (sFile[0])
	{
		fdIn = open(sFile, O_RDONLY);
	}
	else
	{
		fdIn = STDIN_FILENO;
	}

	if (fdIn == -1)
	{
		perror("Cannot open input file");
		return 0;
	}

	struct stat buffer;
	fstat(fdIn, &buffer);
	bitV *readBytes = newVec(buffer.st_size * 8);
	ssize_t n = read(fdIn, readBytes->v, buffer.st_size);

	bitV *readCodes = newVec(KB);
	for (int i = 0; i < n; i += 1)
	{
		appendStack(readCodes, codes[readBytes->v[i]]);
	}

	int i;
	for (i = 0; i < (readCodes->f / 8) + 1; i += 1)
	{

		write(outputFildes, &(readCodes->v[i]), sizeof(readCodes->v[i]));
	}
	return (uint64_t) readCodes->f + 1;
}

void printStatistics(uint64_t sFileBits, uint64_t oFileBits, uint16_t leaves)
{
	printf("Original %u bits: ", sFileBits);
	printf("leaves %u (%u bytes) ", leaves, (3 * leaves) - 1);
	printf("encoding %u bits (%.4f%)\n", oFileBits, ((float) oFileBits / sFileBits) * 100);
}
