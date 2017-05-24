# include "stack.h"
# include <stdio.h>

int main(void)
{
	int i = 431;
	int j = 2190;
	int k = 96;

	stack *s = newStack(1);
	push(s, &i);
	push(s, &j);
	push(s, &k);
	printStack(s);
	printf("i: %p %d\n", (void *) &i, i);
	printf("j: %p %d\n", (void *) &j, j);
	printf("k: %p %d\n", (void *) &k, k);

	printf("\n-------- popping --------\n");
	int *ptr = pop(s);
	printStack(s);
	printf("ptr: %p %d\n", ptr, *ptr);
	
	delStack(s);
	
	return 0;
}
