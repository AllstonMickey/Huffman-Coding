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

# ifndef INVALID
# define INVALID "<%HIS-NAME-WAS-SETH-RICH%>"
# endif

bool moveToFront; // moves found nodes to the front of a linked list if true

/*
 * Statistic Global Variables
 */

uint32_t seekCount;   // iterations of a linked list
uint32_t findLLCount; // calls to findLL()
uint32_t dictCount;   // forbidden words in badspeak.txt
uint32_t tranCount;   // translations in newspeak.txt
uint32_t textCount;   // words read in from stdin using yylex()

/*
 * Flex Scanner Global Variables
 */

int yylex(void);     // runs the scanner until it reaches a token.  Returns the token.
extern char *yytext;  // when yylex returns its token, this holds the char* it found
extern FILE *yyin;   // file from which the scanner gets input from (def: stdin)
int freeFlexScanner(void);

/*
 * Function prototypes
 */

char *stol(char *s); // converts a string to lowercase
FILE *gatherBadspeak(bloomF *bf1, bloomF *bf2, hashTable *ht); // hashes keys into BFs and HT
FILE *gatherNewspeak(bloomF *bf1, bloomF *bf2, hashTable *ht); // hashes keys into BFs and HT
void thoughtcrimeLetter(void); // prints a thoughtcrime message
void goodspeakLetter(void); // prints a goodspeak message
void printWords(listNode *h, bool translate);
void printStats(bloomF *bf1, bloomF *bf2);

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
					perror("getopt [banhammer.c:60]: invalid argument");
					break;
				}
			default:
				{
					perror("getopt [banhammer.c:60]: Something very bad happened");
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

	/*
	 * Read in oldspeak and newspeak words.
	 * Set them in each Bloom Filter and the Hash Table
	 */

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
	 * Add each word to its respective Linked List.
	 */

	listNode *badspeakList = NIL;
	listNode *newspeakList = NIL;
	yyin = stdin;
	while (yylex() != -1)
	{
		textCount += 1;
	
		char *key = stol(yytext);
		if (memBF(filterA, key) && memBF(filterB, key))
		{
			listNode *found = findHT(table, key);
			if (found)
			{
				// badspeak
				if (strcmp(found->newspeak, INVALID) == 0) // no translation implies badspeak
				{
					if (badspeakList == NIL)
					{
						badspeakList = newNode(found->oldspeak, found->newspeak);
					}
					else
					{
						listNode *hasDuplicate = findLL(&badspeakList, found->oldspeak);
						if (hasDuplicate)
						{
							/*
							 * Even though there is a duplicate, finding the node with MTF
							 * changes the head of the list, so we must set the new head.
							 */

							if (moveToFront)
							{
								badspeakList = hasDuplicate;
							}
						}
						else
						{
							badspeakList = insertLL(&badspeakList,
									found->oldspeak, found->newspeak);
						}
					}
				}

				// newspeak
				else
				{
					if (newspeakList == NIL)
					{
						newspeakList = newNode(found->oldspeak, found->newspeak);
					}
					else
					{	
						listNode *hasDuplicate = findLL(&newspeakList, found->oldspeak);
						if (hasDuplicate)
						{
							/*
							 * Even though there is a duplicate, finding the node with MTF
							 * changes the head of the list, so we must set the new head.
							 */
							
							if (moveToFront)
							{
								newspeakList = hasDuplicate;
							}
						}
						else
						{
							newspeakList = insertLL(&newspeakList,
									found->oldspeak, found->newspeak);
						}
					}

				}
			}
		}
		free(key); // free the pointer calloc'd by stol(yytext)
	}

	/*
	 * Print output - statistics or a letter to your comrade
	 */

	if (suppress)
	{
		printStats(filterA, filterB);
	}
	else
	{
		if (badspeakList)
		{
			thoughtcrimeLetter();
			printf("\nYour errors:\n\n");
			printWords(badspeakList, false);
			if (newspeakList)
			{
				printf("\nThink on these words during your vacation!\n\n");
				printWords(newspeakList, true);
			}
		}
		else if (newspeakList)
		{
			goodspeakLetter();
			printWords(newspeakList, true);
		}
	}

	/*
	 * Free and set all pointers used in the program to NIL.
	 */

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

/*
 * String to lowercase
 *
 * @param  s  String to convert to lowercase
 * @return    Lowercase version of s
 */
char *stol(char *s)
{
	// allocate memory for the new string (+1 for the null termination character)
	char *lower = (char *) calloc(strlen(s) + 1, sizeof(char));

	uint32_t i = 0;
	while (s[i] != '\0')
	{
		/*
		 * If uppercase, make it lower, set the result.
		 * If lower, set it.
		 */

		if (s[i] > 64 && s[i] < 91)
		{
			lower[i] = s[i] + 32;
		}
		else
		{
			lower[i] = s[i];
		}
		i += 1;
	}

	// must tell C where the new string ends
	lower[i] = '\0';

	return lower;
}

/*
 * Gathers words from badspeak.txt
 * Sets each word into two Bloom Filters and a Hash Table.
 *
 * @param  bf1    First Bloom Filter
 * @param  bf2    Second Bloom Filter
 * @param  ht     Hash Table of Linked Lists
 * @return NIL    Failure opening file
 * 	   FILE*  File pointer to the opened file
 */
FILE *gatherBadspeak(bloomF *bf1, bloomF *bf2, hashTable *ht)
{
	FILE *badf;
	if (!(badf = fopen("/afs/cats.ucsc.edu/users/g/darrell/badspeak.txt", "r")))
	{
		if (!(badf = fopen("/afs/cats.ucsc.edu/users/j/amickey/cmps12b/assignment3/badspeak.txt", "r")))
		{
			perror("badf [banhammer.c:312]: could not open badspeak.txt");
			return NIL;
		}
	}

	char old[MAXBUFFER];
	while (fscanf(badf, "%s \n", old) != EOF)
	{
		dictCount += 1;
		setBF(bf1, old);
		setBF(bf2, old);
		insertHT(ht, old, INVALID);
	}

	return badf;
}

/*
 * Gathers words from newspeak.txt
 * Sets each word into two Bloom Filters and a Hash Table.
 *
 * @param  bf1    First Bloom Filter
 * @param  bf2    Second Bloom Filter
 * @param  ht     Hash Table of Linked Lists
 * @return NIL    Failure opening file
 * 	   FILE*  File pointer to the opened file
 */
FILE *gatherNewspeak(bloomF *bf1, bloomF *bf2, hashTable *ht)
{
	FILE *newf;
	if (!(newf = fopen("/afs/cats.ucsc.edu/users/g/darrell/newspeak.txt", "r")))
	{
		if (!(newf = fopen("/afs/cats.ucsc.edu/users/j/amickey/cmps12b/assignment3/newspeak.txt", "r")))
		{
			perror("newf [banhammer.c:346]: could not open newspeak.txt");
			return NIL;
		}
	}

	char old[MAXBUFFER];
	char new[MAXBUFFER];
	while (fscanf(newf, "%s %s \n", old, new) != EOF)
	{
		tranCount += 1;
		setBF(bf1, old);
		setBF(bf2, old);
		insertHT(ht, old, new);
	}

	return newf;
}

/*
 * Prints a thoughtcrime letter to your comrade
 * 
 * @param  void
 * @return void
 */
void thoughtcrimeLetter(void)
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

/*
 * Prints a letter of encouragement to your comrade
 *
 * @param  void
 * @return void
 */
void goodspeakLetter(void)
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

/*
 * Prints words in a Linked List
 *
 * @param  h          Head of the Linked List
 * @param  translate  Whether the words in h have a translation
 * @return void
 */
void printWords(listNode *h, bool translate)
{
	listNode *curr = h;
	while (curr != NIL)
	{
		printf("%s", curr->oldspeak);
		if (translate)
		{
			printf(" -> %s", curr->newspeak);
		}
		printf("\n");
		curr = curr->next;
	}
}

/*
 * Prints statistics about the runtime state.
 *
 * @param  bf1   First Bloom Filter
 * @param  bf2   Second Bloom Filter
 * @return void
 */
void printStats(bloomF *bf1, bloomF *bf2)
{
	printf("Seeks %u, ", seekCount);
	printf("Average %lf, ", (double) findLLCount / seekCount);
	printf("Dictionary %u, ", dictCount);
	printf("Translations %u, ", tranCount);
	printf("Text %u, ", textCount);
	printf("Densities: %lf, %lf\n", (double) countBF(bf1) / lenBF(bf1),
					(double) countBF(bf2) / lenBF(bf2));
}

