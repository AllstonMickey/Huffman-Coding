# ifndef NIL
# define NIL (void *) 0
# endif

# ifndef _LL_H
# define _LL_H

# include <stdbool.h>
# include <stdint.h>

extern uint32_t seekCount;
extern uint32_t findLLCount;
extern bool moveToFront;

typedef struct listNode listNode;

struct listNode
{
	char *oldspeak, *newspeak;
	listNode *next;
};
	
listNode *newNode(const char *word, const char *tran);

void delNode(listNode *node);

void delLL(listNode *head);

listNode *insertLL(listNode **head, const char *word, const char *tran);

listNode *findLL(listNode **head, const char *word);

void printLL(listNode *head);

# endif
