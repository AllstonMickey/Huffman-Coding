# include <sys/types.h> // fstat
# include <sys/stat.h>  // fstat
# include <fcntl.h>     // fstat
# include <unistd.h>    // read
# include <getopt.h>
# include <string.h>
# include "bv.h"        // stdint, stdlib, stdio
# include "huffman.h"   // stdlib, stdio, "stack.h"
# include "queue.h"     // stdint, stdbool

# ifndef HIST_LEN
# define HIST_LEN 256
# endif

# ifndef MAX_BUF
# define MAX_BUF 128
# endif

# ifndef BITS
# define BITS 8
# endif

# ifndef EMPTY
# define EMPTY(str) (str[0] == '\0')
# endif

ssize_t loadHist(char *file, uint32_t hist[HIST_LEN]);
uint32_t enqueueHist(queue **q, uint32_t hist[HIST_LEN]);
treeNode *buildTree(queue **q);
uint64_t writeOFile(char oFile[MAX_BUF], char sFile[MAX_BUF], uint64_t sFileBytes,
		uint16_t leaves, treeNode *t, code c[HIST_LEN]);
uint64_t dumpCodes(int outputFildes, char sFile[MAX_BUF], code c[HIST_LEN]);
void printStatistics(uint64_t sFileBits, uint64_t oFileBits, uint16_t leaves);

int main(int argc, char **argv)
{
	char in[MAX_BUF] = {'\0'};  // set input path invalid by default
	char out[MAX_BUF] = {'\0'}; // set output path invalid by default

	bool verbose = false; // print statistics?
	bool pFlag = false;   // print the Huffman tree?
	bool cFlag = false;   // print the codes?
	bool hFlag = false;   // print the histogram?

	int opt;
	while ((opt = getopt(argc, argv, "i:o:Avpch")) != -1)
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
			case 'A':
				{
					verbose = true;
					pFlag = true;
					cFlag = true;
					hFlag = true;
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
			case 'c':
				{
					cFlag = true;
					break;
				}
			case 'h':
				{
					hFlag = true;
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

	while (EMPTY(in))
	{
		printf("Enter an input file path: ");
		scanf("%s", in);
	}

	/*
	 * Create a histogram of the bytes in the sFile.
	 * Sets 0x0 and 0xFF to 1 by default to always construct a tree, regardless of the file.
	 */

	uint32_t histogram[HIST_LEN] = {0};
	histogram[0] = 1;
	histogram[HIST_LEN - 1] = 1;
	uint64_t inputNBytes = (uint64_t) loadHist(in, histogram);

	if (inputNBytes)
	{
		/*
		 * Enqueue the histogram entries as treeNodes.
		 * Build the Huffman Tree.
		 */

		queue *q = newQueue(HIST_LEN + 1); // +1 to account for the empty 0th index of the queue
		uint16_t leafCount = enqueueHist(&q, histogram);
		treeNode *huf = buildTree(&q);

		/*
		 * Create bit paths to each leaf of the Huffman Tree using a stack.
		 */

		code paths[HIST_LEN];
		code s = newCode();
		buildCode(huf, s, paths);

		uint64_t outputNBits = writeOFile(out, in, inputNBytes, leafCount, huf, paths);

		if (verbose)
		{
			printStatistics(inputNBytes * 8, outputNBits, leafCount);
		}
		if (pFlag)
		{
			printTree(huf, 0);
		}
		if (cFlag)
		{
			for (uint16_t i = 0; i < HIST_LEN; i += 1)
			{
				if (histogram[i])
				{
					printf("paths[%u]: ", i);
					printCode(paths[i]);
					printf("\n");
				}
			}
		}
		if (hFlag)
		{
			for (uint16_t i = 0; i < HIST_LEN; i += 1)
			{
				if (histogram[i])
				{
					printf("hist[%u]: %u\n", i, histogram[i]);
				}
			}
		}

		delTree(huf);
		delQueue(q);
	}
	return 0;
}

/* loadHist:
 *
 * Counts the number of occurrences of each byte in a file,
 * storing them in a histogram.
 *
 * Returns the number of bytes read in.
 */
ssize_t loadHist(char *file, uint32_t hist[HIST_LEN])
{
	int fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror("Cannot open input file");
		return 0;
	}

	struct stat buffer;
	fstat(fd, &buffer);
	uint8_t symbol[buffer.st_size];
	ssize_t n = read(fd, symbol, buffer.st_size);

	for (ssize_t i = 0; i < buffer.st_size; i += 1)
	{
		hist[symbol[i]] += 1;
	}

	close(fd);
	return n;
}

/* enqueueHist:
 * 
 * Enqueues all 'active' entries of the histogram as treeNodes.
 * Priority is determined by the count of each node (the freq. in hist.)
 *
 * Returns the number of leaves in the Huffman Tree.
 */
uint32_t enqueueHist(queue **q, uint32_t hist[HIST_LEN])
{
	uint16_t leaves = 0;
	for (uint16_t i = 0; i < HIST_LEN; i += 1)
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
 *
 * Returns the root node of the Huffman Tree as a pointer.
 */
treeNode *buildTree(queue **q)
{
	while ((*q)->head - 1 != ROOT)
	{
		treeNode l, r;
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

/* writeOFile:
 *
 * Writes encoded data to the output file.
 * 1. 32 bits of magicNumber.
 * 2. 64 bits of the size of the source file in bytes.
 * 3. 16 bits of Huffman Tree size
 * 4. Post-order traversal of the tree and visits to interior nodes and leaves
 * 5. Encoded bit paths of the leaves
 *
 * Returns the bits of the codes written to the output file.
 */
uint64_t writeOFile(char oFile[MAX_BUF], char sFile[MAX_BUF], uint64_t sFileBytes,
		uint16_t leaves, treeNode *t, code c[HIST_LEN])
{
	int fdOut;
	if (!EMPTY(oFile))
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
	uint64_t oFileBits = dumpCodes(fdOut, sFile, c);

	close(fdOut);
	return oFileBits;
}

/* dumpCodes:
 *
 * Writes the encoded bit paths of the leaves from the sFile to the oFile.
 *
 * Returns the bits of the codes written to the output file.
 */
uint64_t dumpCodes(int outputFildes, char sFile[MAX_BUF], code c[HIST_LEN])
{
	int fdIn;
	if (!EMPTY(sFile))
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
	uint8_t readBytes[buffer.st_size];
	ssize_t n = read(fdIn, readBytes, buffer.st_size);

	/*
	 * Create a bit vector which holds the paths to the bytes of the sFile.
	 * Loop through the bytes in the sFile, lookup the code/path to the current byte,
	 * and append that code to the bit vector.
	 */

	bitV *readCodes = newVec(KB);
	for (int i = 0; i < n; i += 1)
	{
		appendCode(readCodes, &c[readBytes[i]]);
	}

	uint64_t bvSize = sizeof(readCodes->v[0]) * (readCodes->f / BITS + 1);
	write(outputFildes, readCodes->v, bvSize);
	
	close(fdIn);
	uint64_t oFileBits = readCodes->f;
	delVec(readCodes);
	return oFileBits;
}

void printStatistics(uint64_t sFileBits, uint64_t oFileBits, uint16_t leaves)
{
	printf("Original %lu bits: ", sFileBits);
	printf("leaves %u (%u bytes) ", leaves, (3 * leaves) - 1);
	printf("encoding %lu bits (%.4f%%).\n", oFileBits, ((double) oFileBits / sFileBits) * 100);
}

