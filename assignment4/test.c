# include "stack.h"
# include <stdio.h>

int main(void)
{
	int num = 42;
	stack *s = newStack();
	
	delStack(s);
	return 0;
}
