# include <getopt.h> // get arguments when program was run
# include <unistd.h> // file descriptors, read, open, write, close
# include <fcntl.h>  // file descriptors, read, open, write, close
# include <errno.h>
# include <math.h>   // pow
# include "bf.h"     // Bloom Filters, stdint, stdio, stdlib, and the hash function
# include "hash.h"   // Hash Tables, Linked Lists, stdint, and stdbool

int yylex(void);     // runs the scanner until it reaches a token.  Returns the token.
extern char *yytex;  // when yylex returns its token, this holds the char* it found
extern FILE *yyin;   // file from which the scanner gets input from (def: stdin)

bool moveToFront;    // global variable flag shared with ll.h

void populateBF(bloomF *bf);

int main(int argc, char **argv)
{
	moveToFront = false;
	bool suppress = false;
	uint32_t hashLen = 10000;
	uint32_t bfLen = pow(2, 20);

	int opt;
	while ((opt = getopt(argc, argv, "mbsh:f:")) != -1)
	{
		switch (opt)
		{
			case 'm':
			{
				moveToFront = true;
				break;
			}
			case 'b':
			{
				moveToFront = false;
				break;
			}
			case 's':
			{
				suppress = true;
				break;
			}
			case 'h':
			{
				hashLen = atoi(optarg);
				break;
			}
			case 'f':
			{
				bfLen = atoi(optarg);
				break;
			}
			case '?':
			{
				perror("getopt [banhammer.c:XX]: invalid argument");
				break;
			}
			default:
			{
				perror("getopt [banhammer.c:XX]: Something very bad happened");
				break;
			}
		}
	}
	

	uint32_t initA[] = { 0xDeadD00d, 0xFadedBee, 0xBadAb0de, 0xC0c0aB0a }; // first Bloom Filter salts
	bloomF *filterA = newBF(bfLen, initA);

	uint32_t initB[] = { 0xDeadBeef, 0xFadedB0a, 0xCafeD00d, 0xC0c0aB0a }; // second Bloom Filter salts
	bloomF *filterB = newBF(bfLen, initB);

	uint32_t initH[] = { 0xDeadD00d, 0xFadedBee, 0xBadAb0de, 0xC0c0Babe }; // Hash Table salts
	hashTable *table = newHT(hashLen, initH);

	// read in dictionaries and set BF1 and BF2
	// setBF(bf, key)
	
	FILE *badspeakf;
	badspeakf = fopen("/afs/cats.ucsc.edu/users/g/darrell/badspeak.txt", "r");
	if (badspeakf == NIL)
	{
		badspeakf = fopen("/afs/cats.ucsc.edu/users/j/amickey/cmps12b/assignment3/badspeak.txt", "r");
		if (badspeakf == NIL)
		{
			perror("badspeakf [banhammer.c:XX]: badspeakf is NIL, could not be opened");
			return errno;
		}
	}

	/*
	 * badspeak is opened
	 * read words from badspeak.txt and set the Bloom Filter
	 */
	
	char *old = malloc(sizeof(char) * 100);
	while (fscanf(badspeakf, "%s \n", old) != EOF)
	{
		setBF(filterA, old);
		setBF(filterB, old);
	}

	if (fclose(badspeakf))
	{
		badspeakf = NIL;
		perror("badspeakf [banhammer.c:XX]: badspeakf could not be closed, set pointer to NIL");
		return errno;
	}

	FILE *newspeakf;
	newspeakf = fopen("/afs/cats.ucsc.edu/users/g/darrell/newspeak.txt", "r");
	if (newspeakf == NIL)
	{
		newspeakf = fopen("/afs/cats.ucsc.edu/users/j/amickey/cmps12b/assignment3/newspeak.txt", "r");
		if (newspeakf == NIL)
		{
			perror("newspeakf [banhammer.c:XX]: newspeakf is NIL, could not be opened");
			return errno;
		}
	}

	/*
	 * newspeak is opened
	 * read words and translations from badspeak.txt and set the Bloom Filter
	 */

	char *new = malloc(sizeof(char) * 100);
	while (fscanf(newspeakf, "%s %s \n", old, new) != EOF)
	{
		setBF(filterA, old);
		setBF(filterB, old);
		insertHT(table, old, new);
		printf("%s %s\n", old, new);
	}

	return 0;
}

void populateBF(bloomF *bf)
{

}
