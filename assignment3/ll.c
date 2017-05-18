# include <stdlib.h>   // malloc, free
# include <stdio.h>    // printing
# include <string.h>   // strcmp
# include "strclone.h" // strdup() from <strings.h> implementation because not supported in -std=c99
# include "ll.h"

/*
 * Creates a pointer to a new node.  DOES NOT INSERT it into the list.
 *
 * @param word Oldspeak
 * @param tran Newspeak, translation of word
 * @return A pointer to the new node
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
 * It is recommended to set the head to NIL after this call to prevent access to the its address.
 */
void delLL(listNode *head)
{
	while (head != NIL)
	{
		listNode *next = head->next;
		delNode(head);
		head = next;
	}
}

/*
 * Prepends a node to the front of a list.
 *
 * @param head The 0th node/head of the list.
 * @param word Oldspeak word for the new node.
 * @param tran Newspeak, translation of word for the new node.
 * @return Pointer to the new head of the list.
 */
listNode *insertLL(listNode **head, const char *word, const char *tran)
{
	listNode *newHead = newNode(word, tran);	
	newHead->next = *head;
	return newHead;
}

/*
 * Finds a word in a list.
 * Depending on moveToFront, may move the node containing the word to the head.
 *
 * @param head The 0th node/head of the list.
 * @param word Oldspeak, key to search the list for.
 * @return Pointer to the found node.
 */
listNode *findLL(listNode **head, const char *word)
{
	bool found = false;

	listNode *prev;
	listNode *curr = *head;
	while (curr != NIL && !found)
	{
		if (strcmp(word, curr->oldspeak) == 0)
		{
			found = true;
		}
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}

	if (found)
	{
		if (moveToFront)
		{
			if (curr != *head)
			{
				prev->next = curr->next;
				curr->next = *head;
			}
		}
		return curr;
	}
	return NIL;
}

/*
 * Prints each node's address, members, and addresses of members.
 *
 * @param head The 0th node/head of the list
 * @return void
 */
void printLL(listNode *head)
{
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

