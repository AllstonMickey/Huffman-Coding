# include "stack.h"
# include <stdio.h>

int main(void)
{
	stack *s = newStack();
	delStack(s);
	return 0;
}
