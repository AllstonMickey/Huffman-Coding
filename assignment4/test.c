# include "stack.h"
# include <stdio.h>

int main(void)
{
	int num = 42;
	char c = 'c';
	char str[] = "string";
	
	stack *s = newStack();
	push(s, &num);
	push(s, &c);
	push(s, &str);
	printStack(s);
	printf("num: %p\n", (void *) &num);
	printf("c:   %p\n", (void *) &c);
	printf("str: %p\n", (void *) str);

	printf("\n-------- popping --------\n");
	char *popped;
	pop(s, popped);
	printf("%p %s\n", (void *) popped, popped);
	printStack(s);
	delStack(s);
	return 0;
}
