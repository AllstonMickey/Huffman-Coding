# include <stdlib.h>
# include <stdio.h>
# include "strclone.h" // strdup() from <strings.h> implementation because not supported in -std=c99
# include "ll.h"

extern bool moveToFront;

listNode *newNode(const char *word, const char *tran)
{
	listNode *node = (listNode *) malloc(sizeof(listNode));
	if (node == NIL)
	{
		perror("malloc error [ll.c:10]: node is NIL\n");
	}
	else
	{
		node->oldspeak = strclone(word);
		if (node->oldspeak == NIL)
		{
			perror("malloc error (strclone) [ll.c:17]: node->oldspeak is NIL\n");
		}

		node->newspeak = strclone(tran);
		if (node->newspeak == NIL)
		{
			perror("malloc error (strclone) [ll.c:23]: node->newspeak is NIL\n");
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

