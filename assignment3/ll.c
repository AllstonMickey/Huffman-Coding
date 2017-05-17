# include <stdlib.h>
# include <stdio.h>
# include "strClone.h"
# include "ll.h"

extern bool moveToFront;

listNode *newNode(const char *old, const char *new)
{
	listNode *node = (listNode *) malloc(sizeof(listNode));
	if (node == NIL)
	{
		perror("malloc error [ll.c:16]: node is NIL\n");
	}
	else
	{
		node->oldspeak = strClone(old);
		if (node->oldspeak == NIL)
		{
			perror("malloc error (strdup) [ll.c:23]: node->oldspeak is NIL\n");
		}

		node->newspeak = strClone(new);
		if (node->newspeak == NIL)
		{
			perror("malloc error (strdup) [ll.c:29]: node->newspeak is NIL\n");
		}

		node->next = NIL;
	}
	return node;
}

/*
void delNode(listNode *);

void delLL(listNode *);

listNode *insertLL(listNode **, const char *, const char *);

listNode *findLL(listNode **, const char *);

void printfLL(listNode *);
*/

