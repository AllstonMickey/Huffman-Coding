# include <getopt.h> // get arguments when program was run
# include <unistd.h> // file descriptors, read, open, write, close
# include <fcntl.h>  // file descriptors, read, open, write, close
# include <errno.h>
# include <math.h>   // pow
# include "bf.h"     // Bloom Filters, stdint, stdio, stdlib, and the hash function
# include "hash.h"   // Hash Tables, Linked Lists, stdint, and stdbool

# ifndef MAXBUFFER
# define MAXBUFFER 100
# endif

int yylex(void);     // runs the scanner until it reaches a token.  Returns the token.
extern char *yytext;  // when yylex returns its token, this holds the char* it found
extern FILE *yyin;   // file from which the scanner gets input from (def: stdin)

bool moveToFront;    // global variable flag shared with ll.h

int gatherWords(bloomF *bf1, bloomF *bf2, hashTable *ht); // hashes keys into BFs and HTs
void messageComrade(bloomF *bf1, bloomF *bf2, hashTable *ht); // sends a letter to your comrade

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

	gatherWords(filterA, filterB, table);
	messageComrade(filterA, filterB, table);

	delHT(table);
	delBF(filterB);
	delBF(filterA);

	return 0;
}

/*
 * Gathers words from badspeak.txt and newspeak.txt
 * Sets each oldspeak word into a Bloom Filter.
 * If there is a corresponding newspeak word, insert
 * the oldspeak and newspeak as a Linked List Node in a Hash Table.
 *
 * @param bf1      First Bloom Filter
 * @param bf2      Second Bloom Filter
 * @param ht       Hash Table of pointers to heads of Linked Lists
 * @return errno:  An error occurred while opening or closing a file.
 *         0:      Success
 */
int gatherWords(bloomF *bf1, bloomF *bf2, hashTable *ht)
{
	/*
	 * Try to open badspeak from Darrell's directory.
	 * If it fails, read from my directory.
	 * If that fails, return errno.
	 */

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
	 * badspeak.txt is opened
	 * read words from badspeak.txt and set the Bloom Filters
	 */
	
	char *old = malloc(sizeof(char) * MAXBUFFER);
	while (fscanf(badspeakf, "%s \n", old) != EOF)
	{
		setBF(bf1, old);
		setBF(bf2, old);
	}

	/*
	 * Close badspeak. 
	 * If failed, set the FILE* to NIL and return errno.
	 */

	if (fclose(badspeakf))
	{
		badspeakf = NIL;
		perror("badspeakf [banhammer.c:XX]: badspeakf could not be closed, pointer has been set to NIL");
		return errno;
	}

	/*
	 * Do the same with newspeak.txt but insert the oldspeak and
	 * newspeak words (key and translation) into a Hash Table
	 */

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


	char *new = malloc(sizeof(char) * MAXBUFFER);
	while (fscanf(newspeakf, "%s %s \n", old, new) != EOF)
	{
		setBF(bf1, old);
		setBF(bf2, old);
		insertHT(ht, old, new);
	}

	if (fclose(newspeakf))
	{
		newspeakf = NIL;
		perror("newspeakf [banhammer.c:XX]: newspeakf could not be closed, pointer has been set to NIL");
		return errno;
	}

	free(new);
	free(old);
	return 0; // success
}

void messageComrade(bloomF *bf1, bloomF *bf2, hashTable *ht)
{

	// get all words from stdin until EOF
	yyin = stdin;
	while (yylex() != -1)
	{
		// current word is held in yytext
		// check BF1
		// check BF2
		// find LL
	}
}

