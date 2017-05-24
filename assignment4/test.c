# include "stack.h"
# include <stdio.h>

int main(void)
{
	int num = 42;
	char c = 'c';
	
	stack *s = newStack();
	push(s, &num);
	push(s, &c);
	printStack(s);
	printf("&num: %p\n", (void *) &num);
	printf("&c: %p\n", (void *) &c);
	delStack(s);
	return 0;
}
