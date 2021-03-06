/* Huffman Decode Algorithm Implementation
 */

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

# ifndef EMPTY
# define EMPTY(str) (str[0] == '\0')
# endif

uint64_t readSFile(char *file, uint16_t *leaves, treeNode **h, bitV **b);
treeNode *loadTree(uint8_t savedTree[], uint16_t treeBytes);
void writeOFile(char oFile[MAX_BUF], uint64_t oFileBytes, treeNode *r, bitV *v);
void decodeSymbols(uint8_t sym[], uint64_t oFileBytes, treeNode *r, bitV *v);
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

	while (EMPTY(in))
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
	close(fd);
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
		return;
	}

	if (oFileBytes)
	{
		uint8_t *sym = (uint8_t *) calloc(oFileBytes, sizeof(uint8_t));
		decodeSymbols(sym, oFileBytes, r, v);
		write(fdOut, sym, oFileBytes);
		free(sym);
		sym = NIL;
	}
	close(fdOut);
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
void decodeSymbols(uint8_t sym[], uint64_t oFileBytes, treeNode *r, bitV *v)
{
	treeNode *c = r;    // holds the current node after stepping through the tree.  Start at the root.
	uint64_t len = 0;   // position to store the next symbol
	uint64_t bit_i = 0; // position of the current bit

	while (len < oFileBytes)
	{
		uint32_t val = ((v->v)[bit_i >> 3] & (0x1 << (bit_i % 8))) >> (bit_i % 8);
		int32_t step = stepTree(r, &c, val);
		if (step != -1) // leaf node
		{
			sym[len] = step;
			len += 1;
		}
		bit_i += 1;
	}
}

void printStatistics(uint64_t oFileBits, uint16_t leaves)
{
	printf("Original %lu bits: ", oFileBits);
	printf("leaves %u (%u bytes)\n", leaves, (3 * leaves) - 1);
}

