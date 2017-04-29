# include <stdio.h> // printf, perror
# include <stdlib.h> // atoi, rand & srand, malloc/calloc/realloc/free
# include <getopt.h> // getopt
# include "bv.h"
# include "minsort.h"

int main(int argc, char *argv[])
{
	int printNum = 100, seed = 8222022, capacity = 100;
	
	int opt;
	while ((opt = getopt(argc, argv, "AmbiqMp:r:n:")) != -1)
	{
		switch (opt)
		{
			case 'p':
			{
				printNum = atoi(optarg);
				break;
			}
			case 'r':
			{
				seed = atoi(optarg);
				break;
			}
			case 'n':
			{
				capacity = atoi(optarg);
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

	printf("printNum: %d\n", printNum);
	printf("seed: %d\n", seed);
	printf("capacity: %d\n", capacity);

	return 0;
}

