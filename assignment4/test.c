# include "stack.h"
# include <stdio.h>

int main(void)
{
	stack *s = newStack(4, false);
	item num = 'n';
	push(s, num);
	push(s, 't');
	printBits(s);

	printf("popping...\n");
	
	item res1;
	pop(s, &res1);
	printBits(s);
	printf("res1: %c\n", res1);
	
	item res2;
	pop(s, &res2);
	printBits(s);
	printf("res2: %c\n", res2);
	
	/*
	// for each bit (16 bits -> 2 bytes * 8 bits -> 16 bits)
	for (uint32_t i = 0; i < sizeof(uint16_t) * 8; i += 1)
	{
		bool val = (num & (0x1 << (i % 16))) >> (i % 16);
		printf("val, %u: %u\n", i, val);
	}*/
	
	return 0;
}
