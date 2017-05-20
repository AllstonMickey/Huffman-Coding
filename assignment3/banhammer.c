# include <getopt.h> // get arguments when program was run
# include <unistd.h> // file descriptors, read, open, write, close
# include <fcntl.h>  // file descriptors, read, open, write, close
# include <errno.h>
# include <math.h>   // pow
# include "bf.h"     // Bloom Filters, stdint, stdio, stdlib, and the hash function
# include "hash.h"   // Hash Tables, Linked Lists, stdint, and stdbool

// TODO: document functions
//       implement -s flag

# ifndef MAXBUFFER
# define MAXBUFFER 100
# endif

# ifndef INVALID
# define INVALID "<%HIS-NAME-WAS-SETH-RICH%>"
# endif

int yylex(void);     // runs the scanner until it reaches a token.  Returns the token.
extern char *yytext;  // when yylex returns its token, this holds the char* it found
extern FILE *yyin;   // file from which the scanner gets input from (def: stdin)
int freeFlexScanner(void);

char *stol(char *s);

bool moveToFront;    // global variable flag shared with ll.h

FILE *gatherBadspeak(bloomF *bf1, bloomF *bf2, hashTable *ht); // hashes keys into Bloom Filters
FILE *gatherNewspeak(bloomF *bf1, bloomF *bf2, hashTable *ht);
void thoughtcrimeLetter();
void goodspeakLetter();
void printStatistics();

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

	FILE *badspeakf = gatherBadspeak(filterA, filterB, table);
	if (!badspeakf)
	{
		return errno;
	}

	FILE *newspeakf = gatherNewspeak(filterA, filterB, table);
	if (!newspeakf)
	{
		return errno;
	}

	/*
	 * Get input from stdin using a scanner defined by flex
	 */

	listNode *badspeakList = NIL;
	listNode *newspeakList = NIL;
	yyin = stdin;
	while (yylex() != -1)
	{
		char *key = stol(yytext);
		if (memBF(filterA, key) && memBF(filterB, key))
		{
			listNode *found = findHT(table, key);
			if (found)
			{
				if (strcmp(found->newspeak, INVALID) == 0) // if badspeak
				{
					if (badspeakList == NIL)
					{
						badspeakList = newNode(found->oldspeak, found->newspeak);
					}
					else
					{
						if (findLL(&badspeakList, found->oldspeak) == NIL)
						{
							badspeakList = insertLL(&badspeakList,
									found->oldspeak, found->newspeak);
						}
					}
				}
				else
				{
					if (newspeakList == NIL)
					{
						newspeakList = newNode(found->oldspeak, found->newspeak);
					}
					else
					{
						if (findLL(&newspeakList, found->oldspeak) == NIL)
						{
							newspeakList = insertLL(&newspeakList,
									found->oldspeak, found->newspeak);
						}
					}

				}
			}
		}
		free(key);
	}

	listNode *curr;
	if (badspeakList)
	{
		thoughtcrimeLetter();
		printf("\nYour errors:\n\n");

		curr = badspeakList;
		while (curr != NIL)
		{
			printf("%s\n", curr->oldspeak);
			curr = curr->next;
		}

		if (newspeakList)
		{
			curr = newspeakList;
			printf("\nThink on these words during your vacation!\n\n");
			while (curr != NIL)
			{
				printf("%s -> %s\n", curr->oldspeak, curr->newspeak);
				curr = curr->next;
			}
		}
	}
	else if (newspeakList)
	{
		goodspeakLetter();
		curr = newspeakList;
		while (curr != NIL)
		{
			printf("%s -> %s\n", curr->oldspeak, curr->newspeak);
			curr = curr->next;
		}
	}

	delLL(badspeakList);
	delLL(newspeakList);
	fclose(newspeakf);
	fclose(badspeakf);
	delHT(table);
	delBF(filterB);
	delBF(filterA);

	newspeakList = NIL;
	badspeakList = NIL;
	newspeakf = NIL;
	badspeakf = NIL;
	table = NIL;
	filterB = NIL;
	filterA = NIL;
	freeFlexScanner();
	return 0;
}

char *stol(char *s)
{
	char *lower = (char *) calloc(strlen(s), sizeof(char));
	for (uint32_t i = 0; i < strlen(s); i += 1)
	{
		if (s[i] > 64 && s[i] < 91)
		{
			lower[i] = s[i] + 32;
		}
		else
		{
			lower[i] = s[i];
		}
	}
	return lower;
}

/*
 * Gathers words from badspeak.txt and newspeak.txt
 * Sets each oldspeak word into a Bloom Filter.
 * If there is a corresponding newspeak word, insert
 * the oldspeak and newspeak as a Linked List Node in a Hash Table.
 *
 * @param bf1      First Bloom Filter
 * @param bf2      Second Bloom Filter
 */
FILE *gatherBadspeak(bloomF *bf1, bloomF *bf2, hashTable *ht)
{
	FILE *badf;
	if (!(badf = fopen("/afs/cats.ucsc.edu/users/g/darrell/badspeak.txt", "r")))
	{
		if (!(badf = fopen("/afs/cats.ucsc.edu/users/j/amickey/cmps12b/assignment3/badspeak.txt", "r")))
		{
			perror("badf [banhammer.c:XX]: could not open badspeak.txt");
			return NIL;
		}
	}

	char old[MAXBUFFER];
	while (fscanf(badf, "%s \n", old) != EOF)
	{
		setBF(bf1, old);
		setBF(bf2, old);
		insertHT(ht, old, INVALID);
	}

	return badf;
}

FILE *gatherNewspeak(bloomF *bf1, bloomF *bf2, hashTable *ht)
{
	FILE *newf;
	if (!(newf = fopen("/afs/cats.ucsc.edu/users/g/darrell/newspeak.txt", "r")))
	{
		if (!(newf = fopen("/afs/cats.ucsc.edu/users/j/amickey/cmps12b/assignment3/newspeak.txt", "r")))
		{
			perror("newf [banhammer.c:XX]: could not open newspeak.txt");
			return NIL;
		}
	}

	char old[MAXBUFFER];
	char new[MAXBUFFER];
	while (fscanf(newf, "%s %s \n", old, new) != EOF)
	{
		setBF(bf1, old);
		setBF(bf2, old);
		insertHT(ht, old, new);
	}

	return newf;
}

void thoughtcrimeLetter() // sends a letter to your comrade
{
	char *letter[] = { "Dear Comrade,\n",
		"You have chosen to use degenerate words that may cause hurt",
		"feelings or cause your comrades to think unpleasant thoughts.",
		"This is doubleplus bad. To correct your wrongthink and",
		"save community consensus we will be sending you to joycamp",
		"administered by Miniluv." };

	for (int line = 0; line < 6; line += 1)
	{
		printf("%s\n", letter[line]);
	}

}

void goodspeakLetter() // sends a letter about converting your comrade's oldspeak into newspeak
{
	char *letter[] = { "Dear Comrade,\n",
		"Submitting your text helps to preserve feelings and prevent",
		"badthink. Some of the words that you used are not goodspeak.",
		"The list shows how to turn the oldspeak words into newspeak." };

	for (int line = 0; line < 4; line += 1)
	{
		printf("%s\n", letter[line]);
	}
}

void printStatistics()
{

}

