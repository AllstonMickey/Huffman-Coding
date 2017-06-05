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

// Step through a tree following the code
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

// Parse a Huffman tree to build codes
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

void printNode(treeNode *t)
{
	printf("node %p:\n", (void *) t);
	printf("\tsymbol: %c %u\n", (char) t->symbol, t->symbol);
	printf("\tcount : %lu\n", t->count);
	printf("\t*left : %p\n", (void *) t->left);
	printf("\t*right: %p\n", (void *) t->right);
}

