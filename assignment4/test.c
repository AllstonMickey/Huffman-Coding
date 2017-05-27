# include "stack.h"
# include "queue.h"
# include "bv.h"
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

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

	queue *q = newQueue(5);

	srand(3190231);
	queueItem nums[4] = { 0x0 };
	/*
	// Enqueue Testing (working as of 05/25/17, 19:54)
	printf("enqueueing...\n");
	for (int i = 0; i < 1; i++)
	{
		nums[i] = rand() % 255;
		enqueue(q, nums[i]);
	}
	printQueue(q);

	printf("dequeueing...\n");
	queueItem res[4] = { 0x0 };
	for (int i = 0; i < 1; i++)
	{
		dequeue(q, &res[i]);
		printQueue(q);
	}
	delQueue(q);
	*/

	uint32_t histogram[256];

	int fd = open("/afs/cats.ucsc.edu/users/g/darrell/encode", O_RDONLY);
	struct stat buffer;
	fstat(fd, &buffer);
	printf("%u\n", buffer.st_size);

	//bitV *vec = newVec(len);
	
	
	return 0;
}
