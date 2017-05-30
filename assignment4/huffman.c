# include <stdio.h>
# include <stdlib.h>
# include <ctype.h> // isalnum
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
	delNode(t);
}

/*
// Dump a Huffman tree onto a file
void dumpTree(treeNode *t, int file);

// Build a tree from the saved tree
treeNode *loadTree(uint8_t savedTree[], uint16_t treeBytes);

// Step through a tree following the code
int32_t stepTree(treeNode *root, treeNode **t, uint32_t code);

// Parse a Huffman tree to build codes
void buildCode(treeNode *t, stack bits, stack hist[256]);

// Join two subtrees
treeNode *join(treeNode *l, treeNode *r);
*/

void printTree(treeNode *t, int depth)
{
	if (t && t->leaf)
	{
		if (isalnum(t->symbol))
		{
			spaces(4 * depth);
			printf("%c (%llu)\n", t->symbol, t->count);
		}
		else
		{
			spaces(4 * depth);
			printf("%X (%llu)\n", t->symbol, t->count);
		}
	}
	else if (t)
	{
		spaces(4 * depth);
		printf("% (%llu)\n", t->count);
		printTree(t->left, depth + 1);
		printTree(t->right, depth + 1);
	}
	return;
}
