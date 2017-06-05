# include <sys/types.h> // open
# include <sys/stat.h>  // open
# include <fcntl.h>     // open
# include <unistd.h>    // read
# include <getopt.h>
# include <string.h>
# include "bv.h"
# include "stack.h"

# ifndef MAX_BUF
# define MAX_BUF 128
# endif

# ifndef MAGIC_NUM
# define MAGIC_NUM 0xdeadd00d
# endif

# ifndef BITS
# define BITS 8
# endif

# ifndef LAST_BYTE
# define LAST_BYTE 1
# endif

# ifndef LINE_FEED
# define LINE_FEED 0xA
# endif

uint64_t readSFile(char *file, uint16_t *leaves, treeNode **h, bitV **b);
treeNode *loadTree(uint8_t savedTree[], uint16_t treeBytes);
void writeOFile(char oFile[MAX_BUF], uint64_t oFileBytes, treeNode *r, bitV *v);
void printStatistics(uint64_t oFileBits, uint16_t leaves);

int main(int argc, char **argv)
{
	char in[MAX_BUF] = {'\0'};  // set input path is invalid by default
	char out[MAX_BUF] = {'\0'}; // set output path is invalid by default

	bool verbose = false;
	bool pFlag = false;

	int opt;
	while ((opt = getopt(argc, argv, "i:o:vp")) != -1)
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

	uint16_t leafCount;
	treeNode *huf;
	bitV *bits;
	uint64_t oFileSize = readSFile(in, &leafCount, &huf, &bits);
	
	writeOFile(out, oFileSize, huf, bits);

	/*int fdOut = open(out, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU | S_IRGRP | S_IROTH);

	if (oFileSize)
	{
		uint8_t sym[oFileSize]; // collection of symbols decoded
		uint64_t symLen = 0;
		uint64_t lineFeed_i;    // holds the index of the furthest line feed in the file

		treeNode *c = huf;
		for (uint64_t i = 0; i < bits->l; i += 1)
		{
			uint32_t val = ((bits->v)[i >> 3] & (0x1 << (i % 8))) >> (i % 8);
			int32_t step = stepTree(huf, &c, val);
			if (step != -1)
			{
				if (step == LINE_FEED)
				{
					lineFeed_i = symLen;
				}
				sym[symLen] = step;
				symLen += 1;
			}
		}

		symLen = lineFeed_i + LAST_BYTE;
		for (uint64_t i = 0; i < symLen; i += 1)
		{
			write(fdOut, &sym[i], sizeof(sym[i]));
		}
	}
	*/

	if (verbose)
	{
		printStatistics(oFileSize * BITS, leafCount);
	}
	if (pFlag)
	{
		printTree(huf, 0);
	}

	return 0;
}

void writeOFile(char oFile[MAX_BUF], uint64_t oFileBytes, treeNode *r, bitV *v)
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
		return;
	}

	if (oFileBytes)
	{
		uint8_t sym[oFileBytes]; // collection of symbols decoded
		uint64_t symLen = 0;
		uint64_t lineFeed_i;    // holds the index of the furthest line feed in the file

		/*
		 * For each bit read in,
		 * 	Get its value and step through the tree to the node
		 * 	If the node is a leaf, add it to the collection of symbols.
		 */

		treeNode *c = r;
		for (uint64_t i = 0; i < v->l; i += 1)
		{
			uint32_t val = ((v->v)[i >> 3] & (0x1 << (i % 8))) >> (i % 8);
			int32_t step = stepTree(r, &c, val);
			if (step != -1)
			{
				if (step == LINE_FEED)
				{
					lineFeed_i = symLen;
				}
				sym[symLen] = step;
				symLen += 1;
			}
		}

		/*
		 * By POSIX standard, each file ends with a line feed.
		 * Therefore, only write the bytes up to the line feed
		 * and the last byte after it.
		 */

		symLen = lineFeed_i + LAST_BYTE;
		for (uint64_t i = 0; i < symLen; i += 1)
		{
			write(fdOut, &sym[i], sizeof(sym[i]));
		}
	}
}

uint64_t readSFile(char *file, uint16_t *leaves, treeNode **h, bitV **b)
{
	int fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror("Cannot open input file");
		return 0;
	}

	uint32_t magicNumber;
	read(fd, &magicNumber, sizeof(magicNumber));

	if (magicNumber != MAGIC_NUM)
	{
		printf("Wrong magic number.  Exiting\n");
		close(fd);
		return 1;
	}

	uint64_t oFileBytes;
	read(fd, &oFileBytes, sizeof(oFileBytes));

	uint16_t treeSize;
	read(fd, &treeSize, sizeof(treeSize));
	*leaves = treeSize;

	uint8_t savedTree[treeSize];
	read(fd, savedTree, treeSize);
	treeNode *t = loadTree(savedTree, treeSize);
	*h = t;

	struct stat buffer;
	fstat(fd, &buffer);

	bitV *v = newVec(buffer.st_size * BITS);
	v->l = read(fd, v->v, buffer.st_size) * BITS;
	*b = v;
	return oFileBytes;
}

// Build a tree from the saved tree
treeNode *loadTree(uint8_t savedTree[], uint16_t treeBytes)
{
	stack *s = newStack(treeBytes);
	uint64_t i = 0;
	while (i < treeBytes)
	{	
		if (savedTree[i] == 'L') // leaf
		{
			treeNode *n = newNode(savedTree[i + 1], 0, true);
			push(s, *n);
			i += 2;
		}
		else // interior node
		{
			treeNode l, r;
			pop(s, &r);
			pop(s, &l);
			treeNode *j = join(convert(l), convert(r));
			push(s, *j);
			i += 1;
		}
	}
	treeNode huf;
	pop(s, &huf);
	return convert(huf);
}

void printStatistics(uint64_t oFileBits, uint16_t leaves)
{
	printf("Original %lu bits: ", oFileBits);
	printf("leaves %u (%u bytes)\n", leaves, (3 * leaves) - 1);
}
