# include <stdio.h>
# include <stdlib.h>
# include <ctype.h> // isalnum
# include <unistd.h> // write
# include "huffman.h"

/*struct treeNode
  {
  uint8_t symbol;
  uint64_t count;
  bool leaf;
  treeNode *left, *right;
  };*/

// Create a single node with symbols, count, and leaf or not
treeNode *newNode(uint8_t s, uint64_t c, bool l)
{
	treeNode *t = (treeNode *) malloc(sizeof(treeNode));
	if (t)
	{
		t->symbol = s;
		t->count = c;
		t->leaf = l;
		t->left = NIL;
		t->right = NIL;
		return t;
	}
	return (treeNode *) 0;
}

// Delete a tree of nodes
void delTree(treeNode *t)
{
	if (t == NIL)
	{
		return;
	}

	delTree(t->left);
	delTree(t->right);
	free(t);
}


// Dump a Huffman tree onto a file
void dumpTree(treeNode *t, int fildes)
{
	// traverse left
	// traverse right
	// write to file
	if (t->leaf)
	{
		write(fildes, "L", sizeof(char));
		write(fildes, &(t->symbol), sizeof(t->symbol));
		return;
	}
	else
	{
		dumpTree(t->left, fildes);
		dumpTree(t->right, fildes);
		write(fildes, "I", sizeof(char));
	}
}

/*
// Build a tree from the saved tree
treeNode *loadTree(uint8_t savedTree[], uint16_t treeBytes);

// Step through a tree following the code
int32_t stepTree(treeNode *root, treeNode **t, uint32_t code);
*/

// Parse a Huffman tree to build codes
void buildCode(treeNode *t, stack *s, stack *table[256])
{
	if (t->leaf)
	{
		table[t->symbol] = deepCopyStack(s, true, false);
		printf("[sym %u]: ", t->symbol); // DEBUGGING PRINT
		printStackBits(s); // DEBUGGING PRINT
		return;
	}

	bool tmp;
	pushBit(s, 0);
	buildCode(t->left, s, table);
	popBit(s, &tmp);

	pushBit(s, 1);
	buildCode(t->right, s, table);
	popBit(s, &tmp);
}

// Join two subtrees
treeNode *join(treeNode *l, treeNode *r)
{
	treeNode *j = newNode('$', l->count + r->count, false);
	j->left = l;
	j->right = r;
	return j;
}

treeNode *convert(treeNode t)
{
	treeNode *p = newNode(t.symbol, t.count, t.leaf);
	p->left = t.left;
	p->right = t.right;
	return p;
}

void printTree(treeNode *t, int depth)
{
	if (t)
	{
		printTree(t->left, depth + 1);
		if (t->leaf)
		{
			if (isalnum(t->symbol))
			{
				spaces(4 * depth);
				printf("'%c' (%llu)\n", t->symbol, t->count);
			}
			else
			{
				spaces(4 * depth);
				printf("0x%X (%llu)\n", t->symbol, t->count);
			}
		}
		else
		{
			spaces(4 * depth);
			printf("$ (%llu)\n", t->count);
		}
		printTree(t->right, depth + 1);
	}
	return;
}

void printNode(treeNode *t)
{
	printf("node %p:\n", (void *) t);
	printf("\tsymbol: %c %u\n", (char) t->symbol, t->symbol);
	printf("\tcount : %u\n", t->count);
	printf("\t*left : %p\n", (void *) t->left);
	printf("\t*right: %p\n", (void *) t->right);
}

