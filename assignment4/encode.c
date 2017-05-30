# include <sys/types.h> // fstat
# include <sys/stat.h>  // fstat
# include <fcntl.h>     // fstat
# include <unistd.h>    // read
# include <getopt.h>
# include "bv.h"        // bit vectors, stdint, stdio, stdlib
# include "huffman.h"   // huffman trees, stacks, stdint, stdbool
# include "queue.h"     // queues, heaps, stdint, stdbool

void populateHistogram(char *file, uint32_t hist[]);

int main(int argc, char **argv)
{
	char *in = NIL;
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

	in = "/afs/cats.ucsc.edu/users/g/darrell/encode";
	uint32_t histogram[256] = { 0 };
	histogram[0] = 1;
	histogram[255] = 1;
	populateHistogram(in, histogram);
}

/*
 * Counts the number of occurrences of each byte in a file,
 * storing them in a histogram.
 *
 * @param file Path to the file to read from
 * @param hist Array to store the occurrences
 */
void populateHistogram(char *file, uint32_t hist[])
{
	int fd = open(file, O_RDONLY);
	struct stat buffer;
	fstat(fd, &buffer);

	bitV *v = newVec(buffer.st_size * 8);
	int64_t n = read(fd, v->v, buffer.st_size);
	for (uint64_t i = 0; i < buffer.st_size; i += 1)
	{
		hist[v->v[i]] += 1;
	}
}
