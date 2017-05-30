# include <sys/types.h> // fstat
# include <sys/stat.h>  // fstat
# include <fcntl.h>     // fstat
# include <unistd.h>    // read
# include <getopt.h>
# include "bv.h"        // bit vectors, stdint, stdio, stdlib
# include "huffman.h"   // huffman trees, stacks, stdint, stdbool
# include "queue.h"     // queues, heaps, stdint, stdbool

int main(int argc, char **argv)
{
	char *in;
	char *out = NIL;
	bool verbose = false;

	int opt;
	while ((opt = getopt(argc, argv, "i:o:v")) != -1)
	{
		switch (opt)
		{
			case 'i':
			{
				in = optarg;
				break;
			}
			case 'o':
			{
				out = optarg;
				break;
			}
			case 'v':
			{
				verbose = true;
				break;
			}
			case '?':
			{
				break;
			}
			default:
			{
				break;
			}
		}
	}
	
	/* QUEUE TESTING with treeNode as the item
	treeNode *nodes = calloc(3, sizeof(treeNode));
	
	treeNode *t = newNode(0, 15, false);
	treeNode *l = newNode(0, 7, false);
	treeNode *r = newNode(0, 2, false);
	
	queue *q = newQueue(5);
	enqueue(q, *t); enqueue(q, *l); enqueue(q, *r);
	printQueue(q);

	treeNode res[3];
	dequeue(q, &res[0]);
	printQueue(q);
	dequeue(q, &res[1]);
	printQueue(q);
	dequeue(q, &res[2]);
	printQueue(q);
	*/
}
