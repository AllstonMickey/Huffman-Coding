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
	free(t);
}

/*
// Dump a Huffman tree onto a file
void dumpTree(treeNode *t, int file);

// Build a tree from the saved tree
treeNode *loadTree(uint8_t savedTree[], uint16_t treeBytes);

// Step through a tree following the code
int32_t stepTree(treeNode *root, treeNode **t, uint32_t code);
*/

// Parse a Huffman tree to build codes
void buildCode(treeNode *t, stack s, stack hist[256])
{
	// if leaf
	// 	save code in hist
	// else
	// 	go left
	// 	go right

	bool bit;
	if (t->leaf)
	{
		/* stack s represents the path to the node and so is the code for it
		 * save this stack into a table of variable length codes (hist).
		 *
		 * Since hist['h'] is s, it does not save the current state of s.
		 * Therefore, when s is later modified by traversing the tree for other leaves,
		 * hist['h'] is also modified.
		 */

		hist[t->symbol] = s;
	
		// Printing debug info
		printf("### Saving stack hist[%u] (%llu). . .\n", t->symbol, t->count);
		printStackBits(&hist[t->symbol]);
		printf("### Saved stack  hist[%u] (%llu). . .\n", t->symbol, t->count);
		printf("\t--- state of hist['h']\n");
		printf("\t");printStackBits(&hist['h']);
		printf("\t--- ended hist['h']\n");
		return;
	}
	else
	{
		pushBit(&s, false); // push 0
		buildCode(t->left, s, hist);
		popBit(&s, &bit);

		pushBit(&s, true); // push 1
		buildCode(t->right, s, hist);
		popBit(&s, &bit);
	}
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

