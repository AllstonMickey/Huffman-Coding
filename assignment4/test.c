# include "stack.h"
# include "queue.h"
# include <stdio.h>

int main(void)
{
	printf("test.c : %lu\n", sizeof(stackItem));
	stack *s = newStack(4, false);
	stackItem num = 42;
	push(s, num);
	push(s, 17);
	printStackBits(s);

	printf("popping...\n");
	
	stackItem res1;
	pop(s, &res1);
	printStackBits(s);
	printf("res1: %u\n", res1);
	
	stackItem res2;
	pop(s, &res2);
	printStackBits(s);
	printf("res2: %u\n", res2);

	queue *q = newQueue(5);
	delQueue(q);
	
	return 0;
}
