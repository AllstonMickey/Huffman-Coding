# include <sys/types.h> // open
# include <sys/stat.h>  // open
# include <fcntl.h>     // open
# include <unistd.h>    // read
# include <getopt.h>
# include <string.h>    // strncpy
# include "bv.h"        // bit vectors
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

uint64_t readSFile(char *file, uint16_t *leaves, treeNode **h, bitV **b);
treeNode *loadTree(uint8_t savedTree[], uint16_t treeBytes);
void writeOFile(char oFile[MAX_BUF], uint64_t oFileBytes, treeNode *r, bitV *v);
uint64_t decodeSymbols(uint8_t sym[], treeNode *r, bitV *v);
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

	if (verbose)
	{
		printStatistics(oFileSize * BITS, leafCount);
	}
	if (pFlag)
	{
		printTree(huf, 0);
	}

	delVec(bits);
	delTree(huf);
	return 0;
}

/* readSFile:
 *
 * Scans a file to gather information about:
 * 	magicNumber  Was this file properly encoded?
 * 	oFileBytes   Size of the original, uncompressed file
 * 	treeSize     How big is the Huffman Tree (bytes)?
 * 	savedTree    How was the tree structured? (then reconstructs it)
 * 	v            What are the bit paths being traversed in the tree to decode this file?
 */
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

/* loadTree:
 *
 * Takes in an array of characters which represent a
 * post-order traversal of the Huffman Tree (leaf, leaf, parent).
 *
 * An 'L' (leaf) is followed by the symbol of the node.
 * An 'I' (interior node) has no following symbol.
 *
 * Since the array follows post-order traversal, an interior node is
 * the parent of the two nodes before it. Therefore, we can reconstruct the tree
 * by pushing leaf nodes onto a stack, popping them when encountering an interior node,
 * and pushing a joined tree of the left and right trees back onto the stack.
 */
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
			delNode(n);
			i += 2;
		}
		else // interior node
		{
			treeNode l, r;
			pop(s, &r);
			pop(s, &l);
			treeNode *j = join(convert(l), convert(r));
			push(s, *j);
			delNode(j);
			i += 1;
		}
	}
	treeNode huf;
	pop(s, &huf);
	delStack(s);
	return convert(huf);
}

/* writeOFile:
 *
 * Decodes an encoded file.  Writes the decoded file.
 */
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
		decodeSymbols(sym, r, v);
		
		// oFileBytes: number of bytes in the original, uncompressed file -> write them back
		for (uint64_t i = 0; i < oFileBytes; i += 1)
		{
			write(fdOut, &sym[i], sizeof(sym[i]));
		}
	}
}

/* decodeSymbols:
 *
 * Traverses a Huffman Tree by following the bit paths stored in a vector.
 * If a leaf node is found, store it in a collection of bytes to be written to the output.
 *
 * Also keeps track of the furthest line feed to signal the end of the file by POSIX standards.
 *
 * For each bit
 * 	Step through the tree following the bit's value.
 * 	If a leaf is encountered, store it.
 *
 * Returns the number of symbols decoded.
 */
uint64_t decodeSymbols(uint8_t sym[], treeNode *r, bitV *v)
{
	uint64_t symLen = 0;
	treeNode *c = r; // holds the current node after stepping through the tree.  Start at the root.

	for (uint64_t i = 0; i < v->l; i += 1)
	{
		uint32_t val = ((v->v)[i >> 3] & (0x1 << (i % 8))) >> (i % 8);
		int32_t step = stepTree(r, &c, val);
		if (step != -1) // leaf node
		{
			sym[symLen] = step;
			symLen += 1;
		}
	}

	return symLen;
}

void printStatistics(uint64_t oFileBits, uint16_t leaves)
{
	printf("Original %lu bits: ", oFileBits);
	printf("leaves %u (%u bytes)\n", leaves, (3 * leaves) - 1);
}
