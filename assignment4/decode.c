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

uint64_t readSFile(char *file, treeNode **h, bitV **b);
treeNode *loadTree(uint8_t savedTree[], uint16_t treeBytes);

int main(int argc, char **argv)
{
	char in[MAX_BUF] = {'\0'};
	char out[MAX_BUF] = {'\0'};

	bool verbose = false;
	bool pFlag = false;
	bool cFlag = false;

	int opt;
	while ((opt = getopt(argc, argv, "i:o:Avpc")) != -1)
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

	treeNode *huf;
	bitV *bits;
	uint64_t oFileSize = readSFile(in, &huf, &bits);
	uint8_t s[oFileSize];
	uint64_t s_i = 0;
	printf("oFileSize: %u\n", oFileSize);
	printf("bits->l:   %u\n", bits->l);

	treeNode *c = huf;
	uint32_t code;
	uint8_t sym;
	for (uint64_t i = 0; i < bits->l; i += 1)
	{
		printf("%u", i);
		uint8_t bitVal = ((bits->v)[i >> 3] & (0x1 << (i % 8))) >> (i % 8);
		printf(" (1)");
		if (bitVal == 0)
		{
			printf(" (2)");
			if (c->left)
			{
				if (c->left->symbol == '$')
				{
					printf(" (3)");
					c = c->left;
				}
				else
				{
					printf(" (4)");
					s[s_i++] = c->left->symbol;
					c = huf;
				}
			}
			else
			{
				break;
			}
		}
		else if (bitVal == 1)
		{
			printf(" (5)");
			if (c->right)
			{
				if (c->right->symbol == '$')
				{
					printf(" (6)");
					c = c->right;
				}
				else
				{
					printf(" (7)");
					s[s_i++] = c->right->symbol;
					c = huf;
				}
			}
			else
			{
				break;
			}
		}
		printf("\n");
	}
	
	int fdOut = open(out, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU | S_IRGRP | S_IROTH);
	write(fdOut, s, sizeof(s[s_i]) * oFileSize);
	return 0;
}

uint64_t readSFile(char *file, treeNode **h, bitV **b)
{
	int fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror("Cannot open input file");
		return 0;
	}

	uint32_t magicNumber;
	read(fd, &magicNumber, sizeof(magicNumber));

	printf("Magic number: %u\n", magicNumber);

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

	uint8_t savedTree[treeSize];
	read(fd, savedTree, treeSize);
	treeNode *t = loadTree(savedTree, treeSize);
	*h = t;

	struct stat buffer;
	fstat(fd, &buffer);

	uint64_t leftover =  buffer.st_size - (sizeof(oFileBytes) + sizeof(treeSize) + treeSize);
	bitV *v = newVec(leftover * BITS);
	read(fd, v->v, leftover);
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

