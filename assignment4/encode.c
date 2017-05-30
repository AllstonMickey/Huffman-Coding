# include <sys/types.h> // fstat
# include <sys/stat.h>  // fstat
# include <fcntl.h>     // fstat
# include <unistd.h>    // read
# include <getopt.h>
# include "bv.h"        // bit vectors, stdint, stdio, stdlib
# include "huffman.h"   // huffman trees, stacks (of bits), stdint, stdbool
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
}
