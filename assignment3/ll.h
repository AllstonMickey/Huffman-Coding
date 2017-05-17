# ifndef NIL
# define NIL (void *) 0
# endif

# ifndef MTF
# define MTF true
# endif

# ifndef _LL_H
# define _LL_H

# include <stdbool.h>

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

listNode *insertLL(listNode **, const char *, const char *);

listNode *findLL(listNode **, const char *);

void printLL(listNode *head);

# endif
