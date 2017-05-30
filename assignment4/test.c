# include "queue.h"
# include "bv.h"
# include "huffman.h"
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h> // fstat
# include <sys/stat.h> // fstat
# include <fcntl.h>   // fstat
# include <unistd.h> // read

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
	queueItem nums[5] = { 0x0 };
	///*
	// Enqueue Testing (working as of 05/25/17, 19:54)
	printf("enqueueing...\n");
	for (int i = 0; i < 5; i++)
	{
		nums[i] = rand() % 255;
		enqueue(q, nums[i]);
	}
	printQueue(q);

	printf("dequeueing...\n");
	queueItem res[5] = { 0x0 };
	for (int i = 0; i < 5; i++)
	{
		dequeue(q, &res[i]);
		printQueue(q);
	}
	//*/
	delQueue(q);

	uint32_t histogram[256] = { 0 };
	histogram[0] = 1;
	 histogram[255] = 1;

	int fd = open("/afs/cats.ucsc.edu/users/g/darrell/encode", O_RDONLY);
	struct stat buffer;
	fstat(fd, &buffer);
	printf("bytes in file: %u\n", buffer.st_size);
	
	bitV *v = newVec(buffer.st_size * 8);
	int64_t n = read(fd, v->v, buffer.st_size);
	printf("bytes read in: %d\n", n);
	for (uint64_t i = 0; i < buffer.st_size; i += 1)
	{
		histogram[v->v[i]] += 1;
	}

	for (uint8_t i = 0; i < 255; i += 1)
	{
		//printf("%u: %u\n", i, histogram[i]);
	}

	// TODO: Implement huffman.h
	// 	 Change QUEUETYPE to treeNode in Makefile when done with huffman.c

	treeNode *root = newNode((char) 83, 1, true);
	treeNode *l = newNode((char) 82, 1, true);
	treeNode *r = newNode((char) 84, 1, true);
	root->left = l;
	root->right = r;
	
	treeNode *foo = newNode((char) 75, 1, true);
	l->left = foo;

	treeNode *bar = newNode((char) 76, 1, true);
	r->left = bar;

	treeNode *baz = newNode((char) 74, 1, true);
	l->right = baz;

	delTree(root);

	delVec(v);
	return 0;
}
