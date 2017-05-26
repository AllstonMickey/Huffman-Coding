# include "stack.h"
# include "queue.h"
# include <stdio.h>
# include <stdlib.h>

int main(void)
{
	bool isFixed = false;
	stack *s = newStack(4, isFixed);
	
	// Stack Testing with individual bits (working as of 05/25/17, 18:38)
	/*
	bool bits[5] = { true, false, false, true, false };
	for (int i = 0; i < 5; i += 1)
	{
		pushBit(s, bits[i]);
		printf("%u ", bits[i]);
	}
	printf("\n");

	bool res[5] = {};
	for (int i = 0; i < 5; i += 1)
	{
		popBit(s, &res[i]);
		printf("%u ", res[i]);
	}
	printf("\n");
	*/

	//  Stack Testing with numbers (working as of 05/25/17, 18:38)
	/*
	printf("pushing...\n");

	stackItem new1 = 42;
	push(s, new1);
	printf("new1: %u\n", new1);

	stackItem new2 = 17;
	push(s, new2);
	printf("new2: %u\n", new2);
	
	printf("popping...\n");
	
	stackItem res1;
	pop(s, &res1);
	printf("res1: %u\n", res1);
	
	stackItem res2;
	pop(s, &res2);
	printf("res2: %u\n", res2);
	*/
	delStack(s);

	queue *q = newQueue(10);

	srand(256);
	queueItem nums[7] = { 0x0 };
	
	// Enqueue Testing (working as of 05/25/17, 19:54)
	printf("enqueueing...\n");
	for (int i = 0; i < 7; i += 1)
	{
		nums[i] = rand() % 255;
		enqueue(q, nums[i]);
	}
	printQueue(q);
	
	printf("dequeueing 1...\n");
	queueItem res1;
	dequeue(q, &res1);
	printQueue(q);
	printf("res1: %u\n", res1);

	printf("dequeueing 2...\n");
	queueItem res2;
	dequeue(q, &res2);
	printQueue(q);
	printf("res2: %u\n", res2);

	delQueue(q);
	
	return 0;
}
