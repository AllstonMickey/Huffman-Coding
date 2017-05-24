# include "stack.h"
# include <stdio.h>

int main(void)
{
	stack *s = newStack(20, true);
	push(s, 1);
	push(s, 45);
	push(s, 10);
	push(s, 20);
	push(s, 69);
	printBits(s);
	return 0;
}
