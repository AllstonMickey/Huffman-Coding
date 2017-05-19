# include <getopt.h> // get arguments when program was run
# include <unistd.h> // file descriptors, read, open, write, close
# include <fcntl.h> // file descriptors, read, open, write, close
# include <errno.h>
# include "bf.h"   // Bloom Filters, stdint, stdio, stdlib, and the hash function
# include "hash.h" // Hash Tables, Linked Lists, stdint, and stdbool

bool moveToFront;

int main(int argc, char **argv)
{
	moveToFront = false;
	
	return 0;
}
