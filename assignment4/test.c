# include "stack.h"
# include <stdio.h>

int main(void)
{
	int num = 42;
	char c = 'c';
	char str[] = "string";
	
	stack *s = newStack();
	push(s, &c);
	push(s, &num);
	printStack(s);
	printf("c:   %p\n", (void *) &c);
	printf("num: %p\n", (void *) &num);

	printf("\n-------- popping --------\n");
	int *ptr;
	pop(s, (void *) &ptr);
	printStack(s);
	printf("ptr (popped): %p %d\n", ptr, *ptr);
	delStack(s);
	return 0;
}
