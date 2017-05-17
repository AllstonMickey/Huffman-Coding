# include <stdlib.h>
# include <stdio.h>
# include "strclone.h" // strdup() from <strings.h> implementation because not supported in -std=c99
# include "ll.h"

extern bool moveToFront;

/*
 * Creates a new node.  DOES NOT INSERT it into the list.
 *
 * @param word Oldspeak
 * @param tran Newspeak, translation of word
 * @return The new node
 */
listNode *newNode(const char *word, const char *tran)
{
	listNode *node = (listNode *) malloc(sizeof(listNode));
	if (node == NIL)
	{
		perror("malloc error [ll.c:17]: node is NIL\n");
	}
	else
	{
		node->oldspeak = strclone(word);
		if (node->oldspeak == NIL)
		{
			perror("malloc error (strclone) [ll.c:24]: node->oldspeak is NIL\n");
		}

		node->newspeak = strclone(tran);
		if (node->newspeak == NIL)
		{
			perror("malloc error (strclone) [ll.c:30]: node->newspeak is NIL\n");
		}

		node->next = NIL;
	}
	return node;
}

/*
 * Frees a node and its members from memory.
 * 
 * @param node Node to delete.
 * @return void
 *
 * It is recommended to set the node to NIL after this call to prevent access to its address.
 */
void delNode(listNode *node)
{
	free(node->oldspeak);
	free(node->newspeak);
	free(node);
}

/*
 * Deletes all nodes from a list.
 *
 * @param head The 0th node/head of the list
 * @return void
 *
 * It is recommended to set the head to NIL after this call to prevent access to its address.
 */
void delLL(listNode *head)
{
	listNode *curr = head;
	while (curr->next != NIL)
	{
		delNode(curr);
		curr = curr->next;
	}
	delNode(curr);
}

/*
listNode *insertLL(listNode **, const char *, const char *);

listNode *findLL(listNode **, const char *);
*/

/*
 * Prints each node's address, members, and addresses of members.
 *
 * @param head The 0th node/head of the list
 * @return void
 */
void printLL(listNode *head)
{
	printf("\n------- new -------\n");
	listNode *curr = head;
	while (curr != NIL)
	{
		printf("node: %p\n", (void *) curr);
		printf("\tnext:  %p\n", (void *) curr->next);
		printf("\twords: %s -> %s\n", curr->oldspeak, curr->newspeak);
		printf("\twords addresses: %p -> %p\n", (void *) curr->oldspeak, (void *) curr->newspeak);
		curr = curr->next;
	}
}

