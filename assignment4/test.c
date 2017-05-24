# include "stack.h"
# include <stdio.h>

int main(void)
{
	stack *s = newStack();
	printf("%u\n", empty(s));
	delStack(s);
	return 0;
}
