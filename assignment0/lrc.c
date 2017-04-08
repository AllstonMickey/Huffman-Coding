#include <stdio.h>  // allows use of printf() and scanf()
#include <stdlib.h> // allows use of rand() and srand()

int setNumOfPlayers();

int main()
{
    unsigned int seed; // used for srand(), takes in an unsigned int
    printf("Enter a seed: ");
    scanf("%u", &seed);
    
    signed int numOfPlayers = setNumOfPlayers(); 
    
    return 0;
}

int setNumOfPlayers()
{
    signed int players = 2;
    do
    {    
        if (players < 2 || players > 10)
        {
            printf("\nYou have must at least 2 players and no more than 10.  Try again.\n");
        }
        printf("How many players?: ");
        scanf("%d", &players);
    } while (players < 2 || players > 10);
    
    return players;
}
