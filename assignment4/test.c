# include "stack.h"
# include <stdio.h>

int main(void)
{
	stack *s = newStack(4, false);
	item num = 'n';
	push(s, num);
	push(s, 't');
	printStackBits(s);

	printf("popping...\n");
	
	item res1;
	pop(s, &res1);
	printStackBits(s);
	printf("res1: %c\n", res1);
	
	item res2;
	pop(s, &res2);
	printStackBits(s);
	printf("res2: %c\n", res2);
	
	
	return 0;
}
