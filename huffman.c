# include <ctype.h> // isalnum
# include <unistd.h> // write
# include "huffman.h"

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

// Delete a tree of nodes using post-order traversal.
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


/* dumpTree:
 *
 * Dump the nodes of a tree onto a file using post-order traversal.
 * If the node is a leaf, write 'L' followed by its symbol.
 * Else, it is an interior node, write 'I'.
 */
void dumpTree(treeNode *t, int fildes)
{
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

/* stepTree:
 *
 * Goes down the tree following the value of a bit 'code'.
 * treeNode **t represents the current node after stepping.
 * If the bit is 0, traverse left.  Else, traverse right.
 *
 * If a leaf is found, return its symbol and reset the
 * current node back to the root of the tree.
 *
 */
int32_t stepTree(treeNode *root, treeNode **t, uint32_t code)
{
	if (code == 0)
	{
		if ((*t)->left)
		{
			*t = (*t)->left;
		}
	}
	else
	{
		if ((*t)->right)
		{
			*t = (*t)->right;
		}
	}

	if ((*t)->leaf)
	{
		int32_t sym = (*t)->symbol;
		*t = root;
		return sym;
	}
	else
	{
		return -1;
	}
}

/* buildCode: 
 * 
 * Performs a post-order traversal of the Huffman Tree
 * using a stack, setting the bit paths of each symbol.
 *
 * When traversing left, push 0.
 * When traversing right, push 1.
 *
 * Pop the bit after returning from either traversal.
 */
void buildCode(treeNode *t, code s, code table[256])
{
	if (t->leaf)
	{
		table[t->symbol] = s;
		return;
	}
	
	uint32_t tmp;
	
	pushCode(&s, 0);
	buildCode(t->left, s, table);
	popCode(&s, &tmp);
	
	pushCode(&s, 1);
	buildCode(t->right, s, table);
	popCode(&s, &tmp);
}

/* join:
 *
 * Joins two nodes under one parent node, with its count as
 * the sum of the left and right childrens' counts.
 * 
 * Returns the parent node.
 */
treeNode *join(treeNode *l, treeNode *r)
{
	treeNode *j = newNode('$', l->count + r->count, false);
	j->left = l;
	j->right = r;
	return j;
}

/* convert:
 * 
 * Converts a treeNode to a pointer.
 */
treeNode *convert(treeNode t)
{
	treeNode *p = newNode(t.symbol, t.count, t.leaf);
	p->left = t.left;
	p->right = t.right;
	return p;
}

// credit: DDEL
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
				printf("'%c' (%lu)\n", t->symbol, t->count);
			}
			else
			{
				spaces(4 * depth);
				printf("0x%X (%lu)\n", t->symbol, t->count);
			}
		}
		else
		{
			spaces(4 * depth);
			printf("$ (%lu)\n", t->count);
		}
		printTree(t->right, depth + 1);
	}
	return;
}

